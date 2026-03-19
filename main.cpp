#include <iostream>
#include <cstring>
#include <vector>

class Team;
class Coach;
class Player {
    static int no_players;
    const int id;
    char* name;
    int goal_number;
    int matches_played;
    double* ratings;
    Team* team;
public:
    Player();
    Player(char *, int);
    Player(char *, int, int);
    Player(char*, int, int, double*);
    Player(char*, int, int, double*, Team*);
    Player(const Player &obj);
    ~Player();
    Player& operator=(const Player &obj);
    friend std::ostream& operator<<(std::ostream&, const Player&);
    friend std::istream& operator>>(std::istream&, Player&);
    void setName(const char*);
    const char* getName () const;
    void setTeam(Team* new_team);
    Team* getTeam() const;
};



class Team {
private:
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
};

class Coach {
private:
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
};

class Match {
private:
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
};



int Player::no_players = 0;

Player::Player():id(no_players++) {
    name=strcpy(new char[4], "N/A");
    goal_number=0;
    matches_played=0;
    ratings=nullptr;
    team=nullptr;

}
Player::Player(char *name, int goal_number): id(no_players++) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->goal_number=goal_number;
    matches_played=0;
    ratings=nullptr;
    team=nullptr;
}

Player::Player(char *name, int goal_number, int matches_played): id(no_players++) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->goal_number=goal_number;
    this->matches_played=matches_played;
    ratings=nullptr;
    team=nullptr;
}
Player::Player(char *name, int goal_number, int matches_played, double *ratings): id(no_players++) {
    this->name=strcpy(new char[strlen(name)+1], name);
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
Player::Player(char *name, int goal_number, int matches_played, double *ratings, Team *team): id(no_players++) {
    this->name=strcpy(new char[strlen(name)+1], name);
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

Player::Player(const Player &obj): id(no_players++)
{
    this->name=strcpy(new char[strlen(obj.name) + 1], obj.name);
    this->goal_number=obj.goal_number;
    this->matches_played=obj.matches_played;
    if (obj.matches_played>0){
        this->ratings= new double[obj.matches_played];
        for(int i=0;i<obj.matches_played;i++){
            this->ratings[i]=obj.ratings[i];
        }
    }
    else
    {
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
    this->goal_number=obj.goal_number;
    this->matches_played=obj.matches_played;
    if (obj.matches_played>0){
        this->ratings= new double[obj.matches_played];
        for(int i=0;i<obj.matches_played;i++){
            this->ratings[i]=obj.ratings[i];
        }
    }
    else
    {
        this->ratings=nullptr;
    }
    this->team=obj.team;
    return *this;
}


std::ostream& operator<<(std::ostream& os, const Player &obj)
{
    os<<"Id: "<<obj.id<<"\n";
    if (obj.name)
        os<<"Name: "<<obj.name<<"\n";
    os<<"Goal number: "<<obj.goal_number<<"\n";
    os<<"Matches Played: "<<obj.matches_played<<"\n";
    if (obj.ratings)
    {
        os<<"Ratings: \n" ;
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
    int goal_number;
    int matches;
    int match_rating;
    std::cout<<"Name: ";
    is>>name;
    obj.setName(name);
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

void Player::setTeam(Team* new_team) {
    team=new_team;
}

Team* Player::getTeam() const {
    return team;
}

Team::Team() {
    name=strcpy(new char[4], "N/A");
    headCoach=nullptr;
    budget=0;
}

Team::Team(char *name) {
    this->name=strcpy(new char[strlen(name)+1], name);
    headCoach=nullptr;
    budget=0;
}

Team::Team(char *name, std::vector<Player *>players) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->players=players;
    headCoach=nullptr;
    budget=0;
}
Team::Team(char*name, std::vector<Player*>players, Coach* headCoach) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->players=players;
    this->headCoach=headCoach;
    budget=0;
}

Team::Team(char*name, std::vector<Player*>players, Coach* headCoach, long budget) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->players=players;
    this->headCoach=headCoach;
    this->budget=budget;
}

Team::Team(const Team &obj) {
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
    os<<"Name: "<<obj.name<<"\n";
    os << "Players: \n";
    for (int i = 0; i < obj.players.size(); i++)
        os << *obj.players[i] << "\n";

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

void Team::setName(const char* new_name) {
    delete[] this->name;
    this->name=strcpy(new char[strlen(new_name)+1], new_name);
}

const char* Team::getName() const{
    return this->name;
}



Coach::Coach() {
    name=strcpy(new char[4], "N/A");
    age=0;
    experience_years=0;
    manager_boost=0;
    team=nullptr;
}

Coach::Coach(char *name) {
    this->name=strcpy(new char[strlen(name)+1], name);
    age=0;
    experience_years=0;
    manager_boost=0;
    team=nullptr;
}

Coach::Coach(char *name, int age) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->age=age;
    experience_years=0;
    manager_boost=0;
    team=nullptr;
}


Coach::Coach(char *name, int age, int experience_years) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->age=age;
    this->experience_years=experience_years;
    manager_boost=0;
    team=nullptr;
}

Coach::Coach(char *name, int age, int experience_years, float manager_boost) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->age=age;
    this->experience_years=experience_years;
    this->manager_boost=manager_boost;
    team=nullptr;
}


Coach::Coach(char *name, int age, int experience_years, float manager_boost, Team *team) {
    this->name=strcpy(new char[strlen(name)+1], name);
    this->age=age;
    this->experience_years=experience_years;
    this->manager_boost=manager_boost;
    this->team=team;
}

Coach::Coach(const Coach &obj) {
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

std::ostream &operator<<(std::ostream &os, const Coach &obj) {
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
    std::cout<<"Name: \n";
    is>>name;
    obj.setName(name);
    std::cout<<"Age : \n";
    is>>new_age;
    obj.age=new_age;
    std::cout<<"Years of experience: \n";
    is>>years;
    obj.experience_years=years;
    std::cout<<"Manager boost: \n";
    is>>boost;
    obj.manager_boost=boost;
    return is;
}

Match::Match() {
    home_team=nullptr;
    away_team=nullptr;
    home_possession=0;
    home_shots_on_target=0;
    away_shots_on_target=0;
    home_goals=0;
    away_goals=0;
}
Match::Match(Team *home_team) {
    this->home_team=home_team;
    away_team=nullptr;
    home_possession=0;
    home_shots_on_target=0;
    away_shots_on_target=0;
    home_goals=0;
    away_goals=0;
}
Match::Match(Team *home_team, Team *away_team) {
    this->home_team=home_team;
    this->away_team=away_team;
    home_possession=0;
    home_shots_on_target=0;
    away_shots_on_target=0;
    home_goals=0;
    away_goals=0;
}
Match::Match(Team *home_team, Team *away_team, float home_possession) {
    this->home_team=home_team;
    this->away_team=away_team;
    this->home_possession=home_possession;
    home_shots_on_target=0;
    away_shots_on_target=0;
    home_goals=0;
    away_goals=0;
}

Match::Match(Team *home_team, Team *away_team, float home_possession, int home_shots_on_target) {
    this->home_team=home_team;
    this->away_team=away_team;
    this->home_possession=home_possession;
    this->home_shots_on_target=home_shots_on_target;
    away_shots_on_target=0;
    home_goals=0;
    away_goals=0;
}

Match::Match(Team *home_team, Team *away_team, float home_possession, int home_shots_on_target, int away_shots_on_target) {
    this->home_team=home_team;
    this->away_team=away_team;
    this->home_possession=home_possession;
    this->home_shots_on_target=home_shots_on_target;
    this->away_shots_on_target=away_shots_on_target;
    home_goals=0;
    away_goals=0;
}
Match::Match(Team *home_team, Team *away_team, float home_possession, int home_shots_on_target, int away_shots_on_target, int home_goals) {
    this->home_team=home_team;
    this->away_team=away_team;
    this->home_possession=home_possession;
    this->home_shots_on_target=home_shots_on_target;
    this->away_shots_on_target=away_shots_on_target;
    this->home_goals=home_goals;
    away_goals=0;
}
Match::Match(Team *home_team, Team *away_team, float home_possession, int home_shots_on_target, int away_shots_on_target, int home_goals, int away_goals) {
    this->home_team=home_team;
    this->away_team=away_team;
    this->home_possession=home_possession;
    this->home_shots_on_target=home_shots_on_target;
    this->away_shots_on_target=away_shots_on_target;
    this->home_goals=home_goals;
    this->away_goals=away_goals;
}

Match::Match(const Match &obj) {
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

Team* Match::getHomeTeam() const {
    return home_team;
}

Team* Match::getAwayTeam() const {
    return away_team;
}