#include <string>

using std::string;

const string news[]={"news", "local", "international", "famous", "politics", "science", "games"};
const string games[]={"games"};
const string food[]={"food"};
const string movies[]={"movies"};
const string constellation[]={"constellation"};
const string video[]={"video"};
const string * const caty[]={news, games, food, movies, constellation, video};
/*
 *to access the neo4j database, will be used by both U_NeoDB and L_NeoDB; this
 *class should the socket to prevent the resource leak;
 */

class NeoDB{
public:
    NeoDB();
    int neo_query(const string &, string &);
    bool is_OK(){return state;}
    ~NeoDB();
private:
    int sock;
    bool state;
    NeoDB(NeoDB&);
    NeoDB &operator=(NeoDB);
};

/*
 *U_NeoDB is a interface class that used to access the user's data. the interface
 *of this class is all static, thus do not need create and to forbid create
 *object of this class, constructor declared as private
 */
class U_NeoDB
{
public:
    //static int create_account(const string & account);
    static string search_frd(const string &);
    static string get_client(const string &); //get login client type
    static int set_client(const string &, const string &);  //set login clinet when login
    static int create_account(const string &); //new user
    static int add_friends(const string &, const string &); //add friends
    static int delete_friends(const string &, const string &); //delete friends
    static string get_ip(const string &); //get a specific users ip
    static int set_ip(const string &, const string &); //set ip when login
    static string get_all_fip(const string &); //get all friends ip
    static int set_last_login(const string &, const string &); //set last login time
    static string get_last_login(const string &);//get last login time
    static int is_login(const string &); //test whether login or not
    static int login(const string &, int status); //user login status
    static int set_preference(const string &, const string &, const string &); //prefered objects, first int is category and sub category, second int is the rank level
    static string get_preference(const string &);//get the users prefered items
    static int set_location(const string &, const string &);
    static string get_freq_location(const string &);
    static int set_freq_location(const string &, const string &);
private:
    U_NeoDB();
};

/*
 *L_NeoDB use to manage the location information
 */

class L_NeoDB
{
public:
    static int set_prefer(const string &, int, int);//string is coordinate, first int is the category and subcategory, third is the prefered level;
    static string get_prefer(const string &);
    static int set_new_info(const string &, const string &, int);
private:
    L_NeoDB();
};

int get_ip_location(const string & ipstr, string & xml);