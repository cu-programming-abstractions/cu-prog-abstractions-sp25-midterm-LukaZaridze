#include "maze_solver.h"
#include <stack>
using namespace std;

bool MazeSolver::dfs(Maze& maze, int r, int c, vector<vector<bool>>& visited) {
    // if current position is not valid we should backtrack
    if (!maze.inBounds(r, c) || maze.isWall(r, c) || visited[r][c]) {
        return false;  // happens when we hit a wall or visited a cell
    }

    // if we found an exit, we should start builidng a path back to the start
    if (Cell{r, c} == maze.finish) {
        maze.path.push_back({r, c});  // we keep track of exit position
        return true;
    }

    // mark cell as visited so we dont go around needlessly
    visited[r][c] = true;

    // exploting all possible directions

    // going up
    if (dfs(maze, r - 1, c, visited)) {
        maze.path.push_back({r, c});
        return true;
    }
    // going right
    if (dfs(maze, r, c + 1, visited)) {
        maze.path.push_back({r, c});
        return true;
    }
    // going down
    if (dfs(maze, r + 1, c, visited)) {
        maze.path.push_back({r, c});
        return true;
    }
    // going left
    if (dfs(maze, r, c - 1, visited)) {
        maze.path.push_back({r, c});
        return true;
    }

    // if none of the paths worked, its a dead end
    return false;  // go back and try another path
}

bool MazeSolver::solveDFS(Maze& maze) {
    maze.path.clear();  // clear previus solution attempts

    // create visited tracker
    vector<vector<bool>> visited(maze.grid.size(),
                                 vector<bool>(maze.grid[0].size(), false));

    // start from mazes starting position
    bool found = dfs(maze, maze.start.row, maze.start.col, visited);

    // if we found a path, add the starting position to complete the path
    if (found) {
        maze.path.push_back(maze.start);
    }

    return found;  // return if we escaped the maze or not
}
