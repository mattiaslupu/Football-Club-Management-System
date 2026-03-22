#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

class Team;
class Coach;
class Player {
    static int no_players;
    const int id;
    char* name;
    int age;
    int goal_number;
    int matches_played;
    double* ratings;
    Team* team;
public:
    Player();
    Player(char*, int);
    Player(char*, int, int);
    Player(char*, int, int, int);
    Player(char*, int, int, int, double*);
    Player(char*, int, int, int, double*, Team*);
    Player(const Player &obj);
    ~Player();
    Player& operator=(const Player &obj);
    friend std::ostream& operator<<(std::ostream&, const Player&);
    friend std::istream& operator>>(std::istream&, Player&);
    void setName(const char*);
    const char* getName() const;
    void setAge(int new_age);
    int getAge() const;
    void setTeam(Team* new_team);
    Team* getTeam() const;
    double calculate_value();
    void add_rating(double rating);
    int getId() const;
};


class Team {
private:
    static int no_teams;
    const int id;
    char* name;
    std::vector<Player *> players;
    Coach *headCoach;
    long budget;
public:
    Team();
    Team(char*);
    Team(char*, std::vector<Player*>);
    Team(char*, std::vector<Player*>, Coach*);
    Team(char*, std::vector<Player*>, Coach*, long);
    Team(const Team &obj);
    ~Team();
    Team& operator=(const Team &obj);
    friend std::ostream& operator<<(std::ostream&, const Team&);
    friend std::istream& operator>>(std::istream&, Team&);
    void setName(const char*);
    const char* getName () const;
    double calculate_team_force();
    void pay_salaries();
    void add_player(Player* player);
    void remove_player(int player_id);
    int getId() const;
    int getPlayersCount() const;
    void setHeadCoach(Coach* coach);
};

class Coach {
private:
    static int no_coaches;
    const int id;
    char* name;
    int age;
    int experience_years;
    float manager_boost;
    Team* team;

public:
    Coach();
    Coach(char*);
    Coach(char*, int);
    Coach(char*, int, int);
    Coach(char*, int, int, float);
    Coach(char*, int, int, float, Team*);
    Coach(const Coach &obj);
    ~Coach();
    Coach& operator=(const Coach &obj);
    friend std::ostream& operator<<(std::ostream&, const Coach &);
    friend std::istream& operator>>(std::istream&, Coach &);
    void setName(char *new_name);
    const char* getName() const;
    double effiency_calculator();
    void coach_improvement();
    int getId() const;
    void setTeam(Team*);
};

class Match {
private:
    static int no_matches;
    const int id;
    Team* home_team;
    Team* away_team;
    float home_possession;
    int home_shots_on_target;
    int away_shots_on_target;
    int home_goals;
    int away_goals;
public:
    Match();
    Match(Team*);
    Match(Team*, Team*);
    Match(Team*, Team*, float);
    Match(Team*, Team*, float, int);
    Match(Team*, Team*, float, int, int);
    Match(Team*, Team*, float, int, int, int);
    Match(Team*, Team*, float, int, int, int, int);
    Match(const Match &obj);
    Match& operator=(const Match &obj);
    friend std::ostream& operator<<(std:: ostream& os, const Match& obj);
    friend std::istream& operator>>(std::istream &is, Match& obj);
    void setHomeTeam(Team*);
    void setAwayTeam(Team*);
    Team* getHomeTeam() const;
    Team* getAwayTeam() const;
    double victory_probability();
    void match_simulation();
    int getId() const;
    void setHomePossession(float);
};

class Menu {
private:
    std::vector<Player*> players;
    std::vector<Team*> teams;
    std::vector<Coach*> coaches;
    std::vector<Match*> matches;
public:
    Menu();
    ~Menu();
    void start();
    void player_menu();
    void coach_menu();
    void team_menu();
    void match_menu();
};


int Player::no_players = 0;
int Team::no_teams = 0;
int Coach::no_coaches = 0;
int Match::no_matches = 0;


Player::Player():id(no_players++) {
    name=strcpy(new char[4], "N/A");
    age=0;
    goal_number=0;
    matches_played=0;
    ratings=nullptr;
    team=nullptr;
}

Player::Player(char *name, int goal_number): id(no_players++) {
    this->name=strcpy(new char[strlen(name)+1], name);
    age=0;
    this->goal_number=goal_number;
    matches_played=0;
    ratings=nullptr;
    team=nullptr;
}

Player::Player(char *name, int goal_number, int matches_played): id(no_players++) {
    this->name=strcpy(new char[strlen(name)+1], name);
    age=0;
    this->goal_number=goal_number;
    this->matches_played=matches_played;
    ratings=nullptr;
    team=nullptr;
}

Player::Player(char *name, int age, int goal_number, int matches_played): id(no_players++) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->age=age;
    this->goal_number=goal_number;
    this->matches_played=matches_played;
    ratings=nullptr;
    team=nullptr;
}

Player::Player(char *name, int age, int goal_number, int matches_played, double *ratings): id(no_players++) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->age=age;
    this->goal_number=goal_number;
    this->matches_played=matches_played;
    if (matches_played>0){
        this->ratings=new double[matches_played];
        for(int i=0;i<matches_played;i++){
            this->ratings[i]=ratings[i];
        }
    }
    else this->ratings=nullptr;
    team=nullptr;
}

Player::Player(char *name, int age, int goal_number, int matches_played, double *ratings, Team *team): id(no_players++) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->age=age;
    this->goal_number=goal_number;
    this->matches_played=matches_played;
    if (matches_played>0){
        this->ratings=new double[matches_played];
        for(int i=0;i<matches_played;i++){
            this->ratings[i]=ratings[i];
        }
    }
    else this->ratings=nullptr;
    this->team=team;
}

Player::Player(const Player &obj): id(no_players++) {
    this->name=strcpy(new char[strlen(obj.name) + 1], obj.name);
    this->age=obj.age;
    this->goal_number=obj.goal_number;
    this->matches_played=obj.matches_played;
    if (obj.matches_played>0){
        this->ratings= new double[obj.matches_played];
        for(int i=0;i<obj.matches_played;i++){
            this->ratings[i]=obj.ratings[i];
        }
    }
    else {
        this->ratings=nullptr;
    }
    this->team=obj.team;
}

Player::~Player() {
    delete[] name;
    delete[] ratings;
}

Player &Player::operator=(const Player &obj) {
    if (this == &obj)
        return *this;
    delete[] name;
    delete[] ratings;
    this->name=strcpy(new char[strlen(obj.name)+1], obj.name);
    this->age=obj.age;
    this->goal_number=obj.goal_number;
    this->matches_played=obj.matches_played;
    if (obj.matches_played>0){
        this->ratings= new double[obj.matches_played];
        for(int i=0;i<obj.matches_played;i++){
            this->ratings[i]=obj.ratings[i];
        }
    }
    else {
        this->ratings=nullptr;
    }
    this->team=obj.team;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Player &obj) {
    os<<"Id: "<<obj.id<<"\n";
    if (obj.name)
        os<<"Name: "<<obj.name<<"\n";
    os<<"Age: "<<obj.age<<"\n";
    os<<"Goal number: "<<obj.goal_number<<"\n";
    os<<"Matches Played: "<<obj.matches_played<<"\n";
    if (obj.ratings) {
        os<<"Ratings: \n";
        for (int i=0;i<obj.matches_played;i++)
            os<<"Match "<<i<<": "<<obj.ratings[i]<<"\n";
    }
    if (obj.team != nullptr)
        os << "Team: " << obj.team->getName() << "\n";
    else
        os << "Team: N/A\n";
    return os;
}

std::istream& operator>>(std::istream& is, Player &obj) {
    char name[256];
    int age;
    int goal_number;
    int matches;
    double match_rating;
    std::cout<<"Name: ";
    is>>name;
    obj.setName(name);
    std::cout<<"\n";
    std::cout<<"Age: ";
    is>>age;
    obj.age=age;
    std::cout<<"\n";
    std::cout<<"Goal number: ";
    is>>goal_number;
    obj.goal_number=goal_number;
    std::cout<<"\n";
    std::cout<<"Matches Played: ";
    is>>matches;
    obj.matches_played=matches;
    std::cout<<"\n";
    std::cout<<"Ratings: \n";
    delete[] obj.ratings;
    obj.ratings = new double[obj.matches_played];
    for (int i=0; i<obj.matches_played; i++) {
        std::cout<<"Match "<<i<<": ";
        is>>match_rating;
        obj.ratings[i]=match_rating;
    }
    return is;
}

int Player::getId() const {
    return id;
}

void Player::setName(const char *new_name) {
    if (new_name == nullptr) return;
    if (this->name != nullptr) {
        delete[] this->name;
    }
    this->name = new char[strlen(new_name) + 1];
    strcpy(this->name, new_name);
}

const char *Player::getName() const {
    return this->name;
}

void Player::setAge(int new_age) {
    age=new_age;
}

int Player::getAge() const {
    return age;
}

void Player::setTeam(Team* new_team) {
    team=new_team;
}

Team* Player::getTeam() const {
    return team;
}

double Player::calculate_value() {
    if (matches_played == 0 || ratings == nullptr) return 0;
    double suma=0;
    for (int i=0; i<matches_played; i++) suma+=ratings[i];
    double medie=suma/matches_played;
    double value=((medie*goal_number)/(1+age))*log(matches_played+1);
    return value;

}

void Player::add_rating(double rating) {
    if (rating < 0 || rating > 10) {
        std::cout << "Invalid rating! Must be between 0 and 10.\n";
        return;
    }
    double* new_ratings = new double[matches_played + 1];
    if (ratings != nullptr) {
        for (int i=0; i<matches_played; i++)
            new_ratings[i] = ratings[i];
    }
    new_ratings[matches_played] = rating;
    delete[] ratings;
    ratings = new_ratings;
    matches_played++;
}


Team::Team(): id(no_teams++)  {
    name=strcpy(new char[4], "N/A");
    headCoach=nullptr;
    budget=0;
}

Team::Team(char *name) : id(no_teams++) {
    this->name=strcpy(new char[strlen(name)+1], name);
    headCoach=nullptr;
    budget=0;
}

Team::Team(char *name, std::vector<Player *>players) : id(no_teams++) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->players=players;
    headCoach=nullptr;
    budget=0;
}
Team::Team(char*name, std::vector<Player*>players, Coach* headCoach) : id(no_teams++) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->players=players;
    this->headCoach=headCoach;
    budget=0;
}

Team::Team(char*name, std::vector<Player*>players, Coach* headCoach, long budget) : id(no_teams++) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->players=players;
    this->headCoach=headCoach;
    this->budget=budget;
}

Team::Team(const Team &obj) : id(no_teams++) {
    this->name=strcpy(new char[strlen(obj.name)+1], obj.name);
    this->players=obj.players;
    this->headCoach=obj.headCoach;
    this->budget=obj.budget;
}

Team::~Team() {
    delete[] name;
}

Team &Team::operator=(const Team &obj) {
    if (this==&obj) return *this;
    delete[] name;
    this->name=strcpy(new char[strlen(obj.name)+1], obj.name);
    this->players=obj.players;
    this->headCoach=obj.headCoach;
    this->budget=obj.budget;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Team& obj) {
    os << "Id: " << obj.id << "\n";
    os<<"Name: "<<obj.name<<"\n";
    os << "Players: \n";
    for (int i = 0; i < obj.players.size(); i++)
        os <<" - "<< obj.players[i]->getName() << "\n";

    if (obj.headCoach != nullptr)
        os << "Head Coach: " << obj.headCoach->getName() << "\n";
    else
        os << "Head Coach: N/A\n";
    os<<"Budget: "<<obj.budget;
    return os;
}

std::istream& operator>>(std::istream &is, Team &obj) {
    char name[256];
    long buget;
    std::cout<<"Name:";
    is>>name;
    obj.setName(name);

    std::cout<<"Budget :";
    is>>buget;
    obj.budget=buget;
    return is;
}

int Team::getId() const {
    return id;
}

int Team::getPlayersCount() const{
    return players.size();
}

void Team::setName(const char* new_name) {
    delete[] this->name;
    this->name=strcpy(new char[strlen(new_name)+1], new_name);
}

const char* Team::getName() const{
    return this->name;
}

void Team::setHeadCoach(Coach* coach) {
    headCoach = coach;
}


double Team::calculate_team_force() {
    if (players.empty()) return 0;
    double sum=0;
    for (int i=0; i<players.size(); i++)
        sum+=players[i]->calculate_value();
    sum/=players.size();
    double force=sum;
    if (headCoach != nullptr)
        force += headCoach->effiency_calculator() * 50;
    return force;
}



void Team::pay_salaries() {
    if (players.empty()) return;
    for (int i=0; i<players.size(); i++) {
        long salary = static_cast<long>(players[i]->calculate_value() * 1000);
        budget -= salary;
    }
    std::cout << "Salaries paid. Remaining budget: " << budget << "M€\n";
}

void Team::add_player(Player* player) {
    players.push_back(player);
}

void Team::remove_player(int player_id) {
    for (int i=0; i<players.size(); i++) {
        if (players[i]->getId()==player_id) {
            players[i]->setTeam(nullptr);
            players.erase(players.begin()+i);
            return;
        }
    }
    std::cout<<"Player not found\n";
}

Coach::Coach() : id(no_coaches++) {
    name=strcpy(new char[4], "N/A");
    age=0;
    experience_years=0;
    manager_boost=0;
    team=nullptr;
}

Coach::Coach(char *name): id(no_coaches++) {
    this->name=strcpy(new char[strlen(name)+1], name);
    age=0;
    experience_years=0;
    manager_boost=0;
    team=nullptr;
}

Coach::Coach(char *name, int age) : id(no_coaches++){
    this->name=strcpy(new char[strlen(name)+1], name);
    this->age=age;
    experience_years=0;
    manager_boost=0;
    team=nullptr;
}


Coach::Coach(char *name, int age, int experience_years) : id(no_coaches++){
    this->name=strcpy(new char[strlen(name)+1], name);
    this->age=age;
    this->experience_years=experience_years;
    manager_boost=0;
    team=nullptr;
}

Coach::Coach(char *name, int age, int experience_years, float manager_boost): id(no_coaches++) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->age=age;
    this->experience_years=experience_years;
    this->manager_boost=manager_boost;
    team=nullptr;
}


Coach::Coach(char *name, int age, int experience_years, float manager_boost, Team *team) : id(no_coaches++){
    this->name=strcpy(new char[strlen(name)+1], name);
    this->age=age;
    this->experience_years=experience_years;
    this->manager_boost=manager_boost;
    this->team=team;
}

Coach::Coach(const Coach &obj) : id(no_coaches++) {
    this->name=strcpy(new char[strlen(obj.name)+1], obj.name);
    this->age=obj.age;
    this->experience_years=obj.experience_years;
    this->manager_boost=obj.manager_boost;
    this->team=obj.team;
}

Coach::~Coach() {
    delete[] name;
}

Coach& Coach::operator=(const Coach &obj) {
    if (this==&obj) return *this;
    delete[] name;
    this->name=strcpy(new char[strlen(obj.name)+1], obj.name);
    this->age=obj.age;
    this->experience_years=obj.experience_years;
    this->manager_boost=obj.manager_boost;
    this->team=obj.team;
    return *this;
}

const char *Coach::getName() const {
    return this->name;
}
void Coach::setName(char *new_name) {
    delete[] this->name;
    this->name = strcpy(new char[strlen(new_name)+1], new_name);
}

int Coach::getId() const {
    return id;
}

std::ostream &operator<<(std::ostream &os, const Coach &obj) {
    os << "Id: " << obj.id << "\n";
    os<<"Name: "<<obj.getName()<<"\n";
    os<<"Age :"<<obj.age<<"\n";
    os<<"Years of experience: "<<obj.experience_years<<"\n";
    os<<"Manager boost: "<<obj.manager_boost<<"\n";
    if (obj.team != nullptr)
        os << "Team coached: " << obj.team->getName() << "\n";
    else
        os << "Team coached: N/A\n";
    return os;
}

std::istream &operator>>(std::istream &is, Coach &obj) {
    char name[256];
    int new_age, years;
    float boost;
    std::cout<<"Name: ";
    is>>name;
    obj.setName(name);
    std::cout<<"Age : ";
    is>>new_age;
    obj.age=new_age;
    std::cout<<"Years of experience: ";
    is>>years;
    obj.experience_years=years;
    std::cout<<"Manager boost: ";
    is>>boost;
    obj.manager_boost=boost;
    return is;
}

void Coach::setTeam(Team* new_team) {
    team = new_team;
}

double Coach::effiency_calculator() {
    double effiency;
    effiency=manager_boost*(1+static_cast<double>(experience_years)/20);
    return effiency;
}


void Coach::coach_improvement() {
    this->experience_years++;
    this->manager_boost += 0.1;
}

Match::Match() : id(no_matches++) {
    home_team=nullptr;
    away_team=nullptr;
    home_possession=0;
    home_shots_on_target=0;
    away_shots_on_target=0;
    home_goals=0;
    away_goals=0;
}
Match::Match(Team *home_team) : id(no_matches++)  {
    this->home_team=home_team;
    away_team=nullptr;
    home_possession=0;
    home_shots_on_target=0;
    away_shots_on_target=0;
    home_goals=0;
    away_goals=0;
}
Match::Match(Team *home_team, Team *away_team) : id(no_matches++) {
    this->home_team=home_team;
    this->away_team=away_team;
    home_possession=0;
    home_shots_on_target=0;
    away_shots_on_target=0;
    home_goals=0;
    away_goals=0;
}
Match::Match(Team *home_team, Team *away_team, float home_possession) : id(no_matches++) {
    this->home_team=home_team;
    this->away_team=away_team;
    this->home_possession=home_possession;
    home_shots_on_target=0;
    away_shots_on_target=0;
    home_goals=0;
    away_goals=0;
}

Match::Match(Team *home_team, Team *away_team, float home_possession, int home_shots_on_target) : id(no_matches++) {
    this->home_team=home_team;
    this->away_team=away_team;
    this->home_possession=home_possession;
    this->home_shots_on_target=home_shots_on_target;
    away_shots_on_target=0;
    home_goals=0;
    away_goals=0;
}

Match::Match(Team *home_team, Team *away_team, float home_possession, int home_shots_on_target, int away_shots_on_target) : id(no_matches++) {
    this->home_team=home_team;
    this->away_team=away_team;
    this->home_possession=home_possession;
    this->home_shots_on_target=home_shots_on_target;
    this->away_shots_on_target=away_shots_on_target;
    home_goals=0;
    away_goals=0;
}
Match::Match(Team *home_team, Team *away_team, float home_possession, int home_shots_on_target, int away_shots_on_target, int home_goals) : id(no_matches++) {
    this->home_team=home_team;
    this->away_team=away_team;
    this->home_possession=home_possession;
    this->home_shots_on_target=home_shots_on_target;
    this->away_shots_on_target=away_shots_on_target;
    this->home_goals=home_goals;
    away_goals=0;
}
Match::Match(Team *home_team, Team *away_team, float home_possession, int home_shots_on_target, int away_shots_on_target, int home_goals, int away_goals) : id(no_matches++) {
    this->home_team=home_team;
    this->away_team=away_team;
    this->home_possession=home_possession;
    this->home_shots_on_target=home_shots_on_target;
    this->away_shots_on_target=away_shots_on_target;
    this->home_goals=home_goals;
    this->away_goals=away_goals;
}

Match::Match(const Match &obj) : id(no_matches++) {
    this->home_team=obj.home_team;
    this->away_team=obj.away_team;
    this->home_possession=obj.home_possession;
    this->home_shots_on_target=obj.home_shots_on_target;
    this->away_shots_on_target=obj.away_shots_on_target;
    this->home_goals=obj.home_goals;
    this->away_goals=obj.away_goals;
}

Match &Match::operator=(const Match &obj) {
    if (this==&obj) return *this;
    this->home_team=obj.home_team;
    this->away_team=obj.away_team;
    this->home_possession=obj.home_possession;
    this->home_shots_on_target=obj.home_shots_on_target;
    this->away_shots_on_target=obj.away_shots_on_target;
    this->home_goals=obj.home_goals;
    this->away_goals=obj.away_goals;
    return *this;
}


std::ostream& operator<<(std::ostream& os, const Match& obj) {
    os << "Id: " << obj.id << "\n";
    if (obj.home_team != nullptr)
        os << "Home team: " << obj.home_team->getName() << "\n";
    else
        os << "Home team: N/A\n";

    if (obj.away_team != nullptr)
        os << "Away team: " << obj.away_team->getName() << "\n";
    else
        os << "Away team: N/A\n";

    os << "Home possession: " << obj.home_possession << "%\n";
    os << "Home shots on target: " << obj.home_shots_on_target << "\n";
    os << "Away shots on target: " << obj.away_shots_on_target << "\n";
    os << "Score: " << obj.home_goals << " - " << obj.away_goals << "\n";

    return os;
}

std::istream& operator>>(std::istream& is, Match& obj) {
    float possession;
    int home_shots;
    int away_shots;
    int home_goals;
    int away_goals;
    std::cout << "Home possession: ";
    is >> possession;
    obj.home_possession = possession;
    std::cout<<"\n";
    std::cout << "Home shots on target: ";
    is >> home_shots;
    obj.home_shots_on_target = home_shots;
    std::cout<<"\n";
    std::cout << "Away shots on target: ";
    is >> away_shots;
    obj.away_shots_on_target = away_shots;
    std::cout<<"\n";
    std::cout << "Home goals: ";
    is >> home_goals;
    obj.home_goals = home_goals;
    std::cout<<"\n";
    std::cout << "Away goals: ";
    is >> away_goals;
    obj.away_goals = away_goals;
    return is;
}

void Match::setHomeTeam(Team* new_team) {
    home_team = new_team;
}

void Match::setAwayTeam(Team* new_team) {
    away_team = new_team;
}

void Match::setHomePossession(float possession) {
    home_possession = possession;
}

int Match::getId() const {
    return id;
}

Team* Match::getHomeTeam() const {
    return home_team;
}

Team* Match::getAwayTeam() const {
    return away_team;
}

double Match::victory_probability() {
    if (home_team == nullptr || away_team == nullptr) return 0;
    float possession;
    if (home_possession > 0)
        possession = home_possession;
    else
        possession = 50.0f;
    double home_stats = (home_team->calculate_team_force()*1.1) + (possession*2) + home_shots_on_target;
    double total = home_stats + away_team->calculate_team_force() + (100-possession)*2 + away_shots_on_target;
    return home_stats/total;
}

void Match::match_simulation() {
    if (home_team == nullptr || away_team == nullptr) {
        std::cout << "Teams not set!\n";
        return;
    }
    home_shots_on_target = 0;
    away_shots_on_target = 0;
    home_goals = 0;
    away_goals = 0;
    for (int minut=1; minut<=90; minut++) {
        std::cout << "Minute " << minut << "...\n";
        double random = (double)rand() / RAND_MAX;
        double random2 = (double)rand() / RAND_MAX;
        double prob = victory_probability();
        if (random < 0.03) {
            if (random2 < prob) {
                home_goals++;
                home_shots_on_target++;
                std::cout << "*****GOOOOOOOOL " << home_team->getName() << "!!!!*****\n";
                std::cout << "Score: " << home_goals << " - " << away_goals << "\n";
            } else {
                away_goals++;
                away_shots_on_target++;
                std::cout << "*****GOOOOOOOOL " << away_team->getName() << "!!!!*****\n";
                std::cout << "Score: " << home_goals << " - " << away_goals << "\n";
            }
        } else if (random < 0.15) {
            if (random2 < prob) {
                home_shots_on_target++;
                std::cout << "Shot on target for " << home_team->getName() << " but it was unlucky!\n";
            } else {
                away_shots_on_target++;
                std::cout << "Shot on target for " << away_team->getName() << " but it was unlucky!\n";
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << "\n=== FULL TIME ===\n";
    std::cout << home_team->getName() << " " << home_goals << " - " << away_goals << " " << away_team->getName() << "\n";
    std::cout << "Shots on target: " << home_shots_on_target << " - " << away_shots_on_target << "\n";
}


Menu::Menu() {}

Menu::~Menu() {
    for (int i=0; i<players.size(); i++) delete players[i];
    for (int i=0; i<teams.size(); i++) delete teams[i];
    for (int i=0; i<coaches.size(); i++) delete coaches[i];
    for (int i=0; i<matches.size(); i++) delete matches[i];
}

void Menu::start() {
    bool ok=true;
    int option;
    while (ok==true) {
        std::cout << "========================================\n";
        std::cout << "    FOOTBALL CLUB MANAGEMENT SYSTEM\n";
        std::cout << "========================================\n";
        std::cout << "1. Player\n";
        std::cout << "2. Coach\n";
        std::cout << "3. Team\n";
        std::cout << "4. Match\n";
        std::cout << "0. Exit\n";
        std::cout << "========================================\n";
        std::cout << "Choose an option: ";
        std::cin >> option;

        switch (option) {
            case 1: player_menu(); break;
            case 2: coach_menu(); break;
            case 3: team_menu(); break;
            case 4: match_menu(); break;
            case 0: std::cout << "Goodbye!\n"; ok=false; break;
            default: std::cout << "Invalid option!\n"; break;
        }

    }
}

void Menu::player_menu() {
    int option;
    bool ok=true;
    while (ok) {
    std::cout << "========================================\n";
    std::cout << "           PLAYER MENU\n";
    std::cout << "========================================\n";
    std::cout << "1. Add Player\n";
    std::cout << "2. Display Players\n";
    std::cout << "3. Add Rating\n";
    std::cout << "4. Calculate Value\n";
    std::cout << "0. Back\n";
    std::cout << "========================================\n";
    std::cout << "Choose an option: ";
    std::cin >> option;
        switch (option) {
            case 1: {
                Player *p= new Player();
                std::cin>> *p;
                players.push_back(p);
                break;
            }
            case 2: {
                for (int i=0; i<players.size(); i++)
                    std::cout<<*players[i]<<"\n";
                break;
            }

            case 3: {
                int id;
                double new_rating;
                std::cout<<"Player ID: ";
                std::cin>>id;
                std::cout<<"New rating: ";
                std::cin>>new_rating;
                bool found=false;
                for (int i=0; i<players.size(); i++) {
                    if (players[i]->getId()==id) {
                        players[i]->add_rating(new_rating);
                        found=true;
                    }
                }
                if (!found)
                    std::cout<<"PLayer not found\n";
                break;

            }
            case 4: {
                int id;
                bool found=false;
                std::cout<<"Player ID: ";
                std::cin>>id;
                for (int i=0; i<players.size(); i++) {
                    if (players[i]->getId()==id) {
                        found=true;
                        std::cout<<"Player value: "<<players[i]->calculate_value()<<" M€";
                    }
                }
                if (!found)
                    std::cout<<"PLayer not found\n";
                break;
            }
            case 0: std::cout << "Goodbye!\n"; ok=false; break;
            default: std::cout << "Invalid option!\n"; break;
        }
    }
}


void Menu::team_menu() {
    int option;
    bool ok=true;
    while (ok) {
        std::cout << "========================================\n";
        std::cout << "           TEAM MENU\n";
        std::cout << "========================================\n";
        std::cout << "1. Add Team\n";
        std::cout << "2. Display Teams\n";
        std::cout << "3. Add Player to Team\n";
        std::cout << "4. Remove Player from Team\n";
        std::cout << "5. Set Head Coach\n";
        std::cout << "6. Calculate Team Force\n";
        std::cout << "7. Pay Salaries\n";
        std::cout << "0. Back\n";
        std::cout << "========================================\n";
        std::cout << "Choose an option: ";
        std::cin>>option;
        switch(option) {
            case 1: {
                Team *t= new Team();
                std::cout<<"New Team: ";
                std::cin>>*t;
                teams.push_back(t);
                break;

            }
            case 2: {
                for (int i=0; i<teams.size(); i++)
                    std::cout<<*teams[i]<<"\n";
                break;
            }
            case 3: {
                int team_id, player_id;
                std::cout << "Team id: ";
                std::cin >> team_id;
                std::cout << "Player id: ";
                std::cin >> player_id;
                Team* t = nullptr;
                Player* p = nullptr;
                for (int i=0; i<teams.size(); i++)
                    if (teams[i]->getId() == team_id)
                        t = teams[i];
                for (int i=0; i<players.size(); i++)
                    if (players[i]->getId() == player_id)
                        p = players[i];
                if (t != nullptr && p != nullptr) {
                    t->add_player(p);
                    p->setTeam(t);
                    std::cout << "Player added to team!\n";
                } else {
                    std::cout << "Team or player not found!\n";
                }
                break;
            }
            case 4: {
                int team_id, player_id;
                std::cout << "Team id: ";
                std::cin >> team_id;
                std::cout << "Player id: ";
                std::cin >> player_id;
                Team* t = nullptr;
                for (int i=0; i<teams.size(); i++)
                    if (teams[i]->getId() == team_id)
                        t = teams[i];
                if (t != nullptr) {
                    t->remove_player(player_id);
                    std::cout<<"Player removed from the team\n";
                } else {
                    std::cout << "Team not found!\n";
                }
                break;
            }
            case 5: {
                if (teams.empty() || coaches.empty()) {
                    std::cout << "No teams or coaches!\n";
                    break;
                }
                int team_id, coach_id;
                std::cout << "Team id: ";
                std::cin >> team_id;
                std::cout << "Coach id: ";
                std::cin >> coach_id;
                Team* t = nullptr;
                Coach* c = nullptr;
                for (int i=0; i<teams.size(); i++)
                    if (teams[i]->getId() == team_id)
                        t = teams[i];
                for (int i=0; i<coaches.size(); i++)
                    if (coaches[i]->getId() == coach_id)
                        c = coaches[i];
                if (t != nullptr && c != nullptr) {
                    t->setHeadCoach(c);
                    c->setTeam(t);
                    std::cout << "Head coach set!\n";
                }
                else {
                    std::cout << "Team or coach not found!\n";
                }
                break;
            }
            case 6: {
                int id;
                std::cout<<"Team Id: ";
                std::cin>>id;
                bool found=false;
                for (int i = 0; i < teams.size(); i++) {
                    if ( teams[i]->getId() == id) {
                        std::cout << "Team Force: "<<teams[i]->calculate_team_force()<<"\n";
                        found=true;
                    }
                }
                if (!found) {
                    std::cout<<"Team not found\n";
                }
                break;
            }
            case 7: {
                int id;
                std::cout<<"Team Id: ";
                std::cin>>id;
                bool found=false;
                for (int i = 0; i < teams.size(); i++) {
                    if ( teams[i]->getId() == id) {
                        teams[i]->pay_salaries();
                        found=true;
                    }
                }
                if (!found) std::cout<<"Team not found\n";
                break;
            }
            case 0: std::cout << "Goodbye!\n"; ok=false; break;
            default: std::cout << "Invalid option!\n"; break;
        }
    }
}

void Menu::coach_menu() {
    bool ok=true;
    int option;
    while (ok) {
        std::cout << "========================================\n";
        std::cout << "           COACH MENU\n";
        std::cout << "========================================\n";
        std::cout << "1. Add Coach\n";
        std::cout << "2. Display Coaches\n";
        std::cout << "3. Calculate Efficiency\n";
        std::cout << "4. Improve Coach\n";
        std::cout << "0. Back\n";
        std::cout << "========================================\n";
        std::cout << "Choose an option: ";
        std::cin >> option;
        switch (option) {
            case 1: {
                Coach *c= new Coach();
                std::cin>>*c;
                coaches.push_back(c);
                break;
            }
            case 2: {
                if (coaches.size()!=0) {
                    for (int i=0; i<coaches.size(); i++) {
                        std::cout<<*coaches[i]<<"\n";
                    }
                }
                else std::cout<<"There are no coaches\n";
                break;
            }
            case 3: {
                int id;
                std::cout<<"Coach Id: ";
                std::cin>>id;
                bool found=false;
                for (int i=0; i<coaches.size(); i++) {
                    if (coaches[i]->getId()==id) {
                        found=true;
                        std::cout<<"Coach effiency: "<<coaches[i]->effiency_calculator()<<"\n";
                    }
                }
                if (!found) std::cout<<"Coach not found";
                break;
            }
            case 4: {
                int id;
                std::cout<<"Coach Id: ";
                std::cin>>id;
                bool found=false;
                for (int i=0; i<coaches.size(); i++) {
                    if (coaches[i]->getId()==id) {
                        found=true;
                        std::cout<<"Old efficiency: "<<coaches[i]->effiency_calculator()<<"\n";
                        coaches[i]->coach_improvement();
                        std::cout<<"New efficiency: "<<coaches[i]->effiency_calculator()<<"\n";
                    }
                }
                if (!found) std::cout<<"Coach not found";
                break;
            }
            case 0: std::cout << "Goodbye!\n"; ok=false; break;
            default: std::cout << "Invalid option!\n"; break;
        }
    }
}


void Menu::match_menu() {
    bool ok = true;
    int option;
    while (ok) {
        std::cout << "========================================\n";
        std::cout << "           MATCH MENU\n";
        std::cout << "========================================\n";
        std::cout << "1. Create Match\n";
        std::cout << "2. Display Matches\n";
        std::cout << "3. Set Home Team\n";
        std::cout << "4. Set Away Team\n";
        std::cout << "5. Set Possession\n";
        std::cout << "6. Victory Probability\n";
        std::cout << "7. Simulate Match\n";
        std::cout << "0. Back\n";
        std::cout << "========================================\n";
        std::cout << "Choose an option: ";
        std::cin >> option;
        switch (option) {
            case 1: {
                Match *m = new Match();
                matches.push_back(m);
                std::cout << "Match created with id: " << m->getId() << "\n";
                break;
            }
            case 2: {
                if (matches.size()!=0) {
                    for (int i = 0; i<matches.size(); i++) {
                        std::cout<<*matches[i]<<"\n";
                    }
                }
                else std::cout<<"There are no matches\n";
                break;
            }
            case 3: {
                int match_id, team_id;
                std::cout << "Match id: ";
                std::cin >> match_id;
                std::cout << "Team id: ";
                std::cin >> team_id;
                Match* m = nullptr;
                Team* t = nullptr;
                for (int i=0; i<matches.size(); i++)
                    if (matches[i]->getId() == match_id)
                        m = matches[i];
                for (int i=0; i<teams.size(); i++)
                    if (teams[i]->getId() == team_id)
                        t = teams[i];
                if (m != nullptr && t != nullptr) {
                    m->setHomeTeam(t);
                    std::cout << "Home team set!\n";
                }
                else std::cout << "Match or team not found!\n";
                break;
            }
            case 4: {
                int match_id, team_id;
                std::cout << "Match id: ";
                std::cin >> match_id;
                std::cout << "Team id: ";
                std::cin >> team_id;
                Match* m = nullptr;
                Team* t = nullptr;
                for (int i=0; i<matches.size(); i++)
                    if (matches[i]->getId() == match_id)
                        m = matches[i];
                for (int i=0; i<teams.size(); i++)
                    if (teams[i]->getId() == team_id)
                        t = teams[i];
                if (m != nullptr && t != nullptr) {
                    m->setAwayTeam(t);
                    std::cout << "Away team set!\n";
                }
                else std::cout << "Match or team not found!\n";
                break;
            }
            case 5: {
                int match_id;
                float possession;
                std::cout << "Match Id: ";
                std::cin >> match_id;
                std::cout<<"Possession for the Home Team: ";
                std::cin>>possession;
                bool found=false;
                for (int i=0; i<matches.size(); i++) {
                    if (matches[i]->getId() == match_id) {
                        found=true;
                        matches[i]->setHomePossession(possession);
                    }
                }
                if (!found) std::cout<<"Match not found\n";
                break;
            }
            case 6: {
                int match_id;
                std::cout << "Match Id: ";
                std::cin >> match_id;
                bool found=false;
                for (int i=0; i<matches.size(); i++) {
                    if (matches[i]->getId() == match_id) {
                        found=true;
                        std::cout<<"Probability of the home team to win: "<<matches[i]->victory_probability()*100<<"%\n";
                    }
                }
                if (!found) std::cout<<"Match not found\n";
                break;
            }
            case 7: {
                int match_id;
                std::cout << "Match Id: ";
                std::cin >> match_id;
                bool found=false;
                for (int i=0; i<matches.size(); i++) {
                    if (matches[i]->getId() == match_id) {
                        found=true;
                        std::cout<<"The match is about to begin!!!\n";
                        matches[i]->match_simulation();
                    }
                }
                if (!found) std::cout<<"Match not found\n";
                break;
            }
            case 0: ok = false; break;
            default: std::cout << "Invalid option!\n"; break;
        }
    }
}

int main() {
    srand(time(0));
    Menu menu;
    menu.start();
    return 0;
}