#include <iostream>
using namespace std;
#include<deque>
#include<list>
#include<vector>
#include <algorithm>

class Coordinate {
private:
  int m_row;
  int m_col;

public:
  Coordinate(int r = 0, int c = 0): m_row(r), m_col(c) {
  }

  void addRow(int val) { m_row += val; }
  void addCol(int val) { m_col += val; }
  void setRow(int val) { m_row = val; }
  void setCol(int val) { m_col = val; }
  int getRow() const { return m_row;  }
  int getCol() const { return m_col; }

  bool operator==(const Coordinate& obj) const {
    return m_row == obj.m_row && m_col == obj.m_col;
  }
  bool operator!=(const Coordinate& obj) const {
    return m_row != obj.m_row || m_col != obj.m_col;
  }
  
  void print() const {
    cout << "(" << m_row << "," << m_col << ") ";
  }
  void println() const {
    print();
    cout << endl;
  }
};

/*
Following 4 tasks to do:
1. take apt data structure to maintain snake body
4. implement move()
*/

class SnakeGame {
public:
  enum class DIR
  {
    FORWARD, // right 
    BACKWARD, // left
    UP,
    DOWN
  };
  
  deque<Coordinate> m_SnakeBody;
  
  private:
  Coordinate m_dimension; // dimension of the screen
  Coordinate m_foodPos; // current food position
  DIR m_currDir = DIR::FORWARD; // current direction: F: forward, B: backward, U:up, D:down
  
  string getDirStr(DIR dir) const {
    string retVal;
    switch( dir ) {
    case DIR::FORWARD:
      retVal = "Forward";
      break;
    case DIR::BACKWARD:
      retVal = "Backward";
      break;
    case DIR::UP:
      retVal = "Up";
      break;
    case DIR::DOWN:
      retVal = "Down";
      break;
    }

    return retVal;
  }
  public:
  
  SnakeGame(int width, int height) {
    m_dimension.setRow(width);
    m_dimension.setCol(height);
    populateFood();
  }
  
  int check_food_update_snake(Coordinate curr_pos)
  {

    if( isCollidingWithSnake(curr_pos) ) {
          cout << "GAME IS OVER !!! your score is " << m_SnakeBody.size() << endl;
          return -1;
        }
    if(m_foodPos == curr_pos)
    {
        m_SnakeBody.push_front(curr_pos);
        populateFood();
    }
    else
    {
        Coordinate prev = m_SnakeBody.front();
        for(int i=1; i<m_SnakeBody.size(); i++)
        {
            m_SnakeBody[i] = prev;
            prev = m_SnakeBody[i];
        }
        m_SnakeBody[0] = curr_pos;
    }
    return 0;
  }
            
  int move(DIR dir) 
  { // snake can't move 180 degree 
      cout << "Next move direction: " << getDirStr(dir) <<endl;
      // campute next move
      m_currDir = dir;
    
        switch( dir ) {

        case DIR::FORWARD:
        {
            auto curr_pos = m_SnakeBody.front();
            curr_pos.setCol((curr_pos.getCol() + 1 + m_dimension.getCol()) % m_dimension.getCol());
            if(check_food_update_snake(curr_pos) == -1)
                return -1;
            break;
        }
            
        case DIR::BACKWARD:
            cout<<"Position is not allowed"<<endl;
            break;
    
        case DIR::UP:
        {
            auto curr_pos = m_SnakeBody.front();
            curr_pos.setRow((curr_pos.getRow() - 1 +  m_dimension.getRow()) % m_dimension.getRow());
            if(check_food_update_snake(curr_pos) == -1)
                return -1;
            break;
        }
        case DIR::DOWN:
        {
            auto curr_pos = m_SnakeBody.front();
            curr_pos.setRow((curr_pos.getRow() + 1 + m_dimension.getCol()) % m_dimension.getRow());
            if(check_food_update_snake(curr_pos) == -1)
                return -1;
            break;
        }

        }
        
       cout << "next move coordinate is: ";
       m_SnakeBody.front().println();
       // if snake consumes food --> 1. snake length should grow by one 2. populateFood() should be called to make food appear
      return 0; // returning nonero means either game is over or no place is vacant to allocate for food
  }
  
  list<Coordinate> foods = { {3,2}, {2,3}, {1,1} };
  int populateFood() { // should randomly generate food coordinate by making sure that it is not colliding with snake
        // this function should basically set m_foodPos to vacant cell. If cell is available return 0 else non-zero value
        
    m_foodPos = foods.front();
    foods.pop_front();
    return 0;
  }
  
  
  bool isCollidingWithSnake(const Coordinate& newPos) const {
    return any_of(m_SnakeBody.begin(), m_SnakeBody.end(), [&newPos]( const Coordinate& pos) { return pos == newPos; });
  }
  
  
  void print() const {
    cout << "Snake: ";
    for( auto itr : m_SnakeBody )
      itr.print();
    cout << " Current direction: " << getDirStr(m_currDir) << endl;
    cout << "Food: ";
    m_foodPos.println();
    cout << "---------------------------------\n";
  }
  
};

int main()
{
  SnakeGame game(4, 4);
  vector<SnakeGame::DIR> moves = {
    SnakeGame::DIR::UP,
    SnakeGame::DIR::FORWARD,
    SnakeGame::DIR::BACKWARD,
    SnakeGame::DIR::FORWARD,
    SnakeGame::DIR::UP,
    SnakeGame::DIR::FORWARD,
    SnakeGame::DIR::BACKWARD,
    SnakeGame::DIR::DOWN,
    SnakeGame::DIR::DOWN };
    
    for( auto itr : moves ) {
    game.print();
    game.move(itr);
  }
  
  return 0;
}
