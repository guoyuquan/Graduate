#include <string>
struct rp2p{
    unsigned char confld;
    unsigned char reserv;
    short seq;
    short ack;
    short cksum;
};

/*
 **************************
 confld|reserv|sequence_num
 **************************
 acknowledge  |checksum
 **************************
 */
#define LOG_IN   0x80  //when this bit is set, it's login action
#define SIGN_ON  0x40  //when this bit is set, it's register action
#define LOG_OUT  0x20  //when this bit is set, it's log out action
#define LOGGED   0x10  //when this bit is set, the user has complete login action
/*
 * following four all need the logged flag is set, Otherwise, error occur
 */
#define UPD_IP   0x08  //this bit set for users update it's IP
#define UPD_LOC  0x04  //this bit set for users to update its location
#define UPD_FRD  0x02  //this bit set for users to update friendship
#define UPD_INFO 0x01  //this bit set for request update peer's IP

#define H_MASK   0xf0
#define L_MASK   0x0f


class Action
{
public:
    static int sign_on(const char *);
    static int login(const char *, std::string &);
    static int keep_alive(const char *, unsigned char, unsigned char, std::string &);
    static int log_out(const char *);
};

int proc_msg(const char *, std::string &, int);

