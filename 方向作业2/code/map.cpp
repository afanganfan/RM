#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#pragma pack(push, 1)
struct STLTriangle {
    float normal[3];
    float v1[3], v2[3], v3[3];
    uint16_t attributes;
};
#pragma pack(pop)

// 应用旋转矩阵到顶点
void rotateVertex(const float in[3], float out[3]) {
    out[0] = in[0];              // X' = X
    out[1] = in[2];              // Y' = Z
    out[2] = -in[1];             // Z' = -Y
}

int main() {
    // 文件路径
    const string stl_file = "/home/dtc/map/code/RMUC2025.STL";
    
    // 打开 STL 文件
    ifstream file(stl_file, ios::binary);
    if (!file) {
        cerr << "无法打开文件: " << stl_file << endl;
        return -1;
    }

    // 跳过80字节头部
    file.seekg(80);
    
    // 读取三角形数量
    uint32_t num_triangles;
    file.read(reinterpret_cast<char*>(&num_triangles), 4);

    // 读取所有三角形
    vector<STLTriangle> triangles(num_triangles);
    file.read(reinterpret_cast<char*>(triangles.data()), num_triangles * sizeof(STLTriangle));

    // 处理顶点数据
    vector<Point2f> all_vertices;
    for (auto& tri : triangles) {
        float rotated[3][3];
        rotateVertex(tri.v1, rotated[0]);
        rotateVertex(tri.v2, rotated[1]);
        rotateVertex(tri.v3, rotated[2]);
        
        // 收集所有顶点
        for (int i = 0; i < 3; ++i) {
            all_vertices.emplace_back(rotated[i][0], rotated[i][1]);
        }
    }

    // 计算地图范围
    auto [min_x, max_x] = minmax_element(all_vertices.begin(), all_vertices.end(),
        [](const Point2f& a, const Point2f& b) { return a.x < b.x; });
    auto [min_y, max_y] = minmax_element(all_vertices.begin(), all_vertices.end(),
        [](const Point2f& a, const Point2f& b) { return a.y < b.y; });

    const float resolution = 0.02f;
    const int width = static_cast<int>((max_x->x - min_x->x) / resolution) + 1;
    const int height = static_cast<int>((max_y->y - min_y->y) / resolution) + 1;

    // 创建地图
    Mat grid_map(height, width, CV_8UC1, Scalar(255));

    // 筛选并绘制障碍物
    const float z_threshold = -10.0f;
    const float z_high = -0.41f;
    
    for (auto& tri : triangles) {
        // 检查三个顶点的高度是否在范围内
        bool valid = true;
        for (int i = 0; i < 3; ++i) {
            const float z = -tri.v1[1]; // 旋转后的 Z 坐标是原始 Y 的负值
            if (z <= z_threshold || z >= z_high) {
                valid = false;
                break;
            }
        }
        if (!valid) continue;

        // 转换顶点到像素坐标
        vector<Point> pts;
        for (auto v : { tri.v1, tri.v2, tri.v3 }) {
            float rotated[3];
            rotateVertex(v, rotated);
            int px = static_cast<int>((rotated[0] - min_x->x) / resolution);
            int py = static_cast<int>((rotated[1] - min_y->y) / resolution);
            
            // 边界裁剪
            px = clamp(px, 0, width - 1);
            py = clamp(py, 0, height - 1);
            
            pts.emplace_back(px, py);
        }

        // 绘制填充三角形
        fillConvexPoly(grid_map, pts, Scalar(0));
    }

    // 保存PGM
    const string pgm_file = "map41.pgm";
    imwrite(pgm_file, grid_map);
    cout << "地图已保存为: " << pgm_file << endl;

    return 0;
}