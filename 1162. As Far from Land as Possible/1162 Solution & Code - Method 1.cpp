/*
LeetCode 1162. 地图分析

你现在手里有一份大小为 N x N 的地图网格 grid, 上面的每个区域单元都用 0 和 1 标记好了. 
其中 0 代表海洋, 1 代表陆地, 你知道距离陆地区域最远的海洋区域是是哪一个吗, 请返回该海洋区域到离它最近的陆地区域的距离. 
这里说的距离是曼哈顿距离: (x0, y0) 和 (x1, y1) 这两个区域之间的距离是 |x0 - x1| + |y0 - y1|. 
如果我们的地图上只有陆地或者海洋, 请返回 -1. 

示例 1:
1   0   1
0   0   0
1   0   1
输入: [[1,0,1],[0,0,0],[1,0,1]]
输出: 2
解释:  
海洋区域 (1, 1) 和所有陆地区域之间的距离都达到最大, 最大距离为 2. 

示例 2: 
1   0   0
0   0   0
0   0   0
输入: [[1,0,0],[0,0,0],[0,0,0]]
输出: 4
解释:  
海洋区域 (2, 2) 和所有陆地区域之间的距离都达到最大, 最大距离为 4. 
 
提示: 
1 <= grid.length == grid[0].length <= 100
grid[i][j] 不是 0 就是 1
*/

/*
求最短路径, 首先应该想到用 BFS. 我们可以从所有陆地处开始一圈一圈向外扩, 每次都将所有陆地的上下左右的海洋修改.
那么最后扩到的海洋就是离陆地最远的海洋距离陆地的最近距离.
但是这道题还有一点区别, 它要我们求的是所有海洋区域到所有陆地区域这个点集的最短距离, 这其实是一个多源最短路的问题,
我们在开始阶段就将所有初始点入队, 这样做相当于有了一个超级源点, 这个源点与所有的初始点都有边, 这样原问题就变成了最原始的 BFS 问题.
首先遍历 grid 矩阵, 找到所有的陆地并加入队列, 并且判断是否全是陆地或者海洋;
每一圈都将当前队列中的陆地依次出队并向外圈扩展, 同时将 distance++, 扩展出的陆地入队准备进行下一圈的扩展;
当最后一片海洋被改为陆地时循环结束, 返回 distance, 注意 distance 需要从 -1 开始, 因为最后一片陆地还在队列中, 循环会多执行一次.
*/

#include <vector>

class Solution {
public:
    int maxDistance(std::vector<std::vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        std::vector<int> dx{0, 0, -1, 1};
        std::vector<int> dy{-1, 1, 0, 0};
        std::queue<std::pair<int, int>> landQueue;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    landQueue.push({i, j});
                }
            }
        }
        if (landQueue.size() == 0 || landQueue.size() == m * n) {
            return -1;
        }
        // 因为最后一块变成陆地的海洋还在队列中, distance 需要从 -1 开始
        int distance = -1;
        while (!landQueue.empty()) {
            int landNum = landQueue.size();
            while (landNum--) {
                auto curLand = landQueue.front();
                landQueue.pop();
                for (int i = 0; i < 4; ++i) {
                    int x = curLand.first + dx[i];
                    int y = curLand.second + dy[i];
                    if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != 0) {
                        continue;
                    }
                    grid[x][y] = 2;
                    landQueue.push({x, y});
                }
            }
            distance++;
        }
        return distance;
    }
};