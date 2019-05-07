#ifndef RUDP_H
# define RUDP_H

# include <SDL2/SDL_net.h>

/*
** delay after which a connetion is closed due to innactivity
*/

# define RUDP_CONNECTION_TIMEOUT 5000

/*
** maximum size of data a packet can transmit
**   (not including UDP/IP and library headers)
*/

# define RUDP_MAXIMUM_DATA_SIZE 1024

/*
** maximum number of packet transiting between 2 peer
**   (low (2~16) if frequent, high (32~512) if sparse)
*/

# define RUDP_MAX_WINDOW 4

/*
** delay after wich a syn packet is considered lost (default aggresive: 500ms,
**   recommended: same as CONNECTION_TIMEOUT: around 5000ms)
*/

# define RUDP_SYN_TIMEOUT 5000

/*
** delay between resending unacknowledged packets
**   (default aggresive: 5ms, recommended 15ms ~ 25ms)
*/

# define RUDP_RESEND_TIMEOUT 10

# define RUDP_OFFSET_TYPE 0
# define RUDP_OFFSET_ACK 1
# define RUDP_OFFSET_CUT 5
# define RUDP_OFFSET_LEN 9
# define RUDP_OFFSET_SIZE 13
# define RUDP_OFFSET_DATA 15

typedef struct s_queue_mode		t_queue_mode;
typedef struct s_packet_out		t_packet_out;
typedef struct s_received_data	t_received_data;
typedef struct s_rudp_window	t_rudp_window;
typedef struct s_rudp_peer		t_rudp_peer;
typedef struct s_rudp			t_rudp;

enum							e_rudp_error
{
	RUDP_ERROR_OK = 0,
	RUDP_ERROR_NULL_POINTER = -1,
	RUDP_ERROR_INVALID_ID = -2,
	RUDP_ERROR_CLOSED_CONNECTION = -3,
	RUDP_ERROR_NO_MEMORY = -4,
	RUDP_ERROR_SDLNET = -5,
	RUDP_ERROR_INVALID_SIZE = -6,
	RUDP_ERROR_MAX_CONNECTIONS = -7,
	RUDP_CONNECTION_REFUSED = -8
};

enum							e_state
{
	RUDP_STATE_INIT,
	RUDP_STATE_ACTIVE,
	RUDP_STATE_CLOSING,
	RUDP_STATE_CLOSED
};

enum							e_state_flags
{
	RUDP_STATE_FLAGS_CLOSED = 0b00000111,
	RUDP_STATE_FLAGS_INIT = 0b01001111,
	RUDP_STATE_FLAGS_ACTIVE = 0b01111111,
	RUDP_STATE_FLAGS_CLOSING = 0b00111011
};

enum							e_type
{
	RUDP_TYPE_NULL = 0,
	RUDP_TYPE_FREE = 1,
	RUDP_TYPE_SYN = 2,
	RUDP_TYPE_ACK = 3,
	RUDP_TYPE_DATA = 4,
	RUDP_TYPE_FIN = 5,
	RUDP_TYPE_NOCONN = 6
};

enum							e_type_bit
{
	RUDP_TYPE_BIT_NULL = 1 << RUDP_TYPE_NULL,
	RUDP_TYPE_BIT_FREE = 1 << RUDP_TYPE_FREE,
	RUDP_TYPE_BIT_SYN = 1 << RUDP_TYPE_SYN,
	RUDP_TYPE_BIT_ACK = 1 << RUDP_TYPE_ACK,
	RUDP_TYPE_BIT_DATA = 1 << RUDP_TYPE_DATA,
	RUDP_TYPE_BIT_FIN = 1 << RUDP_TYPE_FIN,
	RUDP_TYPE_BIT_NOCONN = 1 << RUDP_TYPE_NOCONN
};

/*
** RUDP_NEED_ACK:
**   RUDP_TYPE_BIT_SYN
**   RUDP_TYPE_BIT_DATA
**   RUDP_TYPE_BIT_FIN
*/

#define RUDP_NEED_ACK   0b00110100

/*
** RUDP_RESET_TIME:
**   RUDP_TYPE_NULL
**   RUDP_TYPE_SYN
**   RUDP_TYPE_ACK
**   RUDP_TYPE_DATA
*/

#define RUDP_RESET_TIME 0b00011101

/*
** suggested ports for peer/client/server
*/

#define RUDP_PEER_PORT 0x4242
#define RUDP_SERVER_PORT 0x4444

struct							s_queue_mode
{
	Uint8						need_ack : 1;
	Uint8						can_timeout : 1;
	Uint32						ack;
	int							(*on_ack)(t_rudp*,
											t_rudp_peer*,
											t_packet_out*,
											void *);
	void						*on_ack_data;
	Uint32						timeout;
	int							(*on_timeout)(t_rudp*,
											t_rudp_peer*,
											t_packet_out*,
											void *);
	void						*on_timeout_data;
	Uint32						delay;
};

struct							s_packet_out
{
	struct s_packet_out			*prev;
	struct s_packet_out			*next;
	UDPpacket					*packet;
	t_queue_mode				mode;
	Uint32						tick_queued;
	Uint32						last_sent;
};

/*
** the only type of packet to be bufferized is data
** all other packet are treated as is, ack is kept for
** the seq fields are ignored in reassembled_data
*/

struct							s_received_data
{
	struct s_received_data		*next;
	struct s_received_data		*prev;
	Uint32						seq_no;
	Uint32						seq_start;
	Uint32						seq_len;
	size_t						size;
	Uint8						data[0];
};

typedef struct s_assembled_data	t_assembled_data;

struct							s_assembled_data
{
	size_t						size;
	size_t						cursor;
	Uint8						*data;
};

struct							s_rudp_window
{
	t_received_data		*received_data;
	t_assembled_data	assembled_data;
	t_packet_out		*queue;
};

struct							s_rudp_peer
{
	Uint8						instigator : 1;
	Uint8						hand_shook : 1;
	Uint32						last_recv;
	Uint32						seq_no;
	Uint32						target_seq_no;
	Uint32						state;
	SDL_mutex					*mutex;
	int							(*state_function)(t_rudp*,
													UDPpacket*,
													t_rudp_peer*);
	IPaddress					targeted;
	t_rudp_window				window;
};

/*
** callbacks:
*/

typedef int						(*t_connection_attempt_callback)(t_rudp *,
																	UDPpacket *,
																	void *);

typedef int						(*t_received_free_packet_callback)(t_rudp *,
																	UDPpacket *,
																	void *);

/*
** main object:
*/

struct							s_rudp
{
	Uint16							port_in;
	Uint16							port_out;
	UDPsocket						listener_socket;
	UDPsocket						sender_socket;
	Uint32							nb_connections;
	Uint32							used_connections;
	int								running;
	Uint32							initial_seq_no;
	t_rudp_peer						*peers;
	SDL_Thread						*listener_thread;
	SDL_Thread						*sender_thread;
	char							*name;
	enum e_rudp_error				errno;
	t_connection_attempt_callback	connection_attempt_callback;
	void							*connection_attempt_user_data;
	t_received_free_packet_callback	received_free_packet_callback;
	void							*received_free_packet_user_data;
};

/*
** interface:
*/

t_rudp							*rudp_init(char *name, Uint16 port_in,
										Uint16 port_out,
										Uint32 maximum_number_of_connections);
int								rudp_close(t_rudp *rudp);
int								rudp_connect(t_rudp *rudp, const char ip[]);
int								rudp_disconnect(t_rudp *rudp, int id);
int								rudp_send(t_rudp *rudp, int id, void *data,
											Uint64 size);
int								rudp_receive(t_rudp *rudp, int id, void *data,
											int max_size);
int								rudp_send_free(t_rudp *rudp, IPaddress target,
												int size, void *data);
int								rudp_attach_free_receiver(t_rudp *rudp,
						t_received_free_packet_callback cb, void *user_data);

/*
** return 0: connection validated
** return non-null: connection refused
*/

int								rudp_attach_connection_attempt_receiver(
			t_rudp *rudp, t_connection_attempt_callback cb, void *user_data);

/*
** common:
*/

t_rudp							*rudp(Uint16 port_in, Uint16 port_out,
										Uint32 maximum_number_of_connections);
int								start_rudp(t_rudp *rudp);
void							stop_rudp(t_rudp *rudp);

/*
** peer:
*/

t_rudp_peer						*find_peer(t_rudp *rudp, IPaddress target);
t_rudp_peer						*new_peer(t_rudp *rudp, IPaddress target);
int								peer_switch_state(t_rudp *rudp,
													t_rudp_peer *peer,
													Uint32 state);
t_packet_out					*remove_packet(t_rudp_window *window,
												t_packet_out *pack_out);

/*
** listener:
*/

int								listener_thread(t_rudp *rudp);
void							listener_free_msg(t_rudp *rudp,
													UDPpacket *pack);
int								received_data(t_rudp *rudp, t_rudp_peer *peer,
												UDPpacket *pack);
int								received_ack(t_rudp *rudp, t_rudp_peer *peer,
												Uint32 ack);
void							received_noconn(t_rudp *rudp,
												t_rudp_peer *peer);

/*
** -> states:
*/

int								listener_closed_state(t_rudp *rudp,
														UDPpacket *pack,
														t_rudp_peer *peer);
int								listener_init_state(t_rudp *rudp,
														UDPpacket *pack,
														t_rudp_peer *peer);
int								listener_active_state(t_rudp *rudp,
														UDPpacket *pack,
														t_rudp_peer *peer);
int								listener_closing_state(t_rudp *rudp,
														UDPpacket *pack,
														t_rudp_peer *peer);

/*
** sender:
*/

int								sender_thread(t_rudp *rudp);
t_packet_out					*queue_packet(t_rudp *rudp, t_rudp_peer *peer,
										UDPpacket *packet, t_queue_mode mode);
int								queue_syn_msg(t_rudp *rudp, t_rudp_peer *peer);
int								queue_fin_msg(t_rudp *rudp, t_rudp_peer *peer);

/*
** msg:
*/

int								msg_acknowledge(t_rudp *rudp, Uint32 target,
												Uint32 ack);
int								msg_no_connection(t_rudp *rudp, Uint32 target);

/*
** utility:
*/

Uint32							get_my_local_ip(void);
void							print_packet_info(int padding, UDPpacket *pack);
void							stringify_ip(Uint32 addr, char buff[15]);
const char						*stringify_rudp_error(
													enum e_rudp_error err_code);
const char						*stringify_rudp_state(enum e_state state);
const char						*stringify_type(enum e_type type);
int								in_set(int v, size_t l, int s[]);
Uint16							read_16(const Uint8 *data);
Uint32							read_32(const Uint8 *data);
Uint64							read_64(const Uint8 *data);
void							write_16(Uint8 *data, Uint16 v);
void							write_32(Uint8 *data, Uint32 v);
void							write_64(Uint8 *data, Uint64 v);

#endif
