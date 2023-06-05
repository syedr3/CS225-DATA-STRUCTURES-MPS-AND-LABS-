/* Your code here! */
#include <maze.h>
using namespace std;
using namespace cs225;
SquareMaze::SquareMaze(){

}

bool SquareMaze::canTravel(int x, int y, int dir) const{ //works
    // return true;
if (dir == 0){ //right
    if (x != width_-1 && walls[x][y].right == false )
        return true;
}
if (dir == 1){ //down
    if (y != height_-1 && walls[x][y].down == false )
        return true;
}
if (dir == 2){ //left
    if (x != 0 && walls[x-1][y].right == false )
        return true;
}
if (dir == 3){ //up
    if (y != 0 && walls[x][y-1].down == false )
        return true;
}
return false;
}

cs225::PNG * SquareMaze::drawMaze()const{ //works
    int PNG_width = width_*10+1;
    int PNG_height = height_*10+1;
    cs225::PNG* maze_out = new cs225::PNG(PNG_width,PNG_height);
    for (int n = 0; n < PNG_height; n++)
        {maze_out->getPixel(0,n).l = 0;}
    for (int m = 0; m < PNG_width; m++)
        {maze_out->getPixel(m,0).l = 0;}
    for (int k = 1; k < 10; k++)
        {maze_out->getPixel(k,0).l = 1;}
    for (int i = 0; i < height_; i++){
        for (int j = 0; j < width_; j++){
            if (walls[j][i].down == 1){ //Puts bottom wall
                for (int x = 0; x < 11; x++){
                maze_out->getPixel(j*10+x, (i+1)*10).l = 0;
                }
            }
            if (walls[j][i].right == 1){ //Puts right wall
                for (int x = 0; x < 11; x++){
                maze_out->getPixel((j+1)*10, i*10+x).l = 0;
                }
            }
        }
    }
return maze_out;
}


cs225::PNG * SquareMaze::drawMazeWithSolution(){ //works
PNG* sol_pic = drawMaze();
vector<int> sol = solveMaze();
int x = 5;
int y = 5;
int size = sol.size();
for (int i = 0; i < size; i++) {
    if (sol[i] == 0) {
        for (int j = x; j < x + 11; j++) {
            sol_pic->getPixel(j,y).h = 0;
            sol_pic->getPixel(j,y).s = 1;
            sol_pic->getPixel(j,y).l = 0.5;
            sol_pic->getPixel(j,y).a = 1;
        }
        x = x + 10;
    }
    if (sol[i] == 1) {
        for (int j = y; j < y + 11; j++) {
            sol_pic->getPixel(x,j).h = 0;
            sol_pic->getPixel(x,j).s = 1;
            sol_pic->getPixel(x,j).l = 0.5;
            sol_pic->getPixel(x,j).a = 1;
        }
        y = y + 10;
    }
    if (sol[i] == 2) {
        for (int j = x; j > x - 11; j--) {
            sol_pic->getPixel(j,y).h = 0;
            sol_pic->getPixel(j,y).s = 1;
            sol_pic->getPixel(j,y).l = 0.5;
            sol_pic->getPixel(j,y).a = 1;
        }
        x = x - 10;
    }
    if (sol[i] == 3) {
        for (int j = y; j > y - 11; j--) {
            sol_pic->getPixel(x,j).h = 0;
            sol_pic->getPixel(x,j).s = 1;
            sol_pic->getPixel(x,j).l = 0.5;
            sol_pic->getPixel(x,j).a = 1;
        }
        y = y - 10;
    }
}
x = x - 5;
for (int j = 1; j < 10; j++) {
    sol_pic->getPixel(x + j, height_ * 10).l = 1;
}
return sol_pic;
}

void SquareMaze::makeMaze(int width, int height){ //works
    width_ = width;
    height_ = height;
    walls.resize(width_);
    for (int i = 0; i < width_; i++){
        walls[i].resize(height_);
    }
    DisjointSets smth;
    smth.addelements(width_*height_);
    for (int y = 0; y < height_; y++){
        for (int x = 0; x < width_; x++){
            setWall(x,y,0,true);
            setWall(x,y,1,true);
        }
    }
    int count = 0;
    while (count < width_*height_-1){
        int y = rand() % height_;
        int x = rand() % width_;
        int coordinate = y*width_ + x; //row major order
        int w = rand() % 2;
        if(w == 1){//remove right wall
            if (x != width_-1 && (smth.find(coordinate) != smth.find(coordinate+1))){ //makes sure we don't go into a cycle
                smth.setunion(smth.find(coordinate),smth.find(coordinate+1));
                setWall(x,y,0,false);
                count++;
            }
        }
        if(w == 0){//removes down wall
            if (y != height_-1 && (smth.find(coordinate) != smth.find(coordinate+width_))){ //makes sure we don't go into a cycle
                smth.setunion(smth.find(coordinate),smth.find(coordinate+width_));
                setWall(x,y,1,false);
                count++;
            }
        }
    }
}

void SquareMaze::setWall(int x, int y, int 	dir, bool exists){
    if (dir == 0){
        if(exists == true) 
            walls[x][y].right = true;
        else
            walls[x][y].right = false;
    }
    else{
        if(exists == true)
            walls[x][y].down = true;
        else
            walls[x][y].down = false;
    }
}


vector<int> SquareMaze::solveMaze() { //AMA slides? Finally works
queue<pair<int, int>> q;
vector<vector<bool>> visited(width_, vector<bool>(height_));
vector<vector<pair<int, int>>> prev(width_, vector<pair<int, int>>(height_));
vector<int> last_row(width_);
q.push(make_pair(0, 0));
visited[0][0] = true;
pair<int, int> c;
int length = 0;
while (!q.empty()) {
    c = q.front();
    q.pop();
    int x = c.first;
    int y = c.second;
    if (canTravel(x, y, 0) && !visited[x + 1][y]) {
        q.push(make_pair(x + 1, y));
        visited[x + 1][y] = true;
        prev[x + 1][y] = c;
    }
    if (canTravel(x, y, 1) && !visited[x][y + 1]) {
        q.push(make_pair(x, y + 1));
        visited[x][y + 1] = true;
        prev[x][y + 1] = c;
    }
    if (canTravel(x, y, 2) && !visited[x - 1][y]) {
        q.push(make_pair(x - 1, y));
        visited[x - 1][y] = true;
        prev[x - 1][y] = c;
    }
    if (canTravel(x, y, 3) && !visited[x][y - 1]) {
        q.push(make_pair(x, y - 1));
        visited[x][y - 1] = true;
        prev[x][y - 1] = c;
    }
    if (y == height_ - 1) {
        last_row[x] = length;
    }
    length++;
}
int final_destination = 0;
for (int i = 0; i < width_; i++) {
    if (last_row[i] > last_row[final_destination]) {
        final_destination = i;
    }
}
int ans;
vector<int> sol;
c = make_pair(final_destination, height_ - 1);
while (c != make_pair(0,0)) {
    int dx = c.first - prev[c.first][c.second].first;
    int dy = c.second - prev[c.first][c.second].second;
    if (dx == 1) ans = 0;
    else if (dx == -1) ans = 2;
    else if (dy == 1) ans = 1;
    else ans = 3;
    sol.push_back(ans);
    c = prev[c.first][c.second];
}
vector<int> sol_;
for (int i = sol.size() - 1; i > -1; i--) {
    sol_.push_back(sol[i]);
}
return sol_;
}
