#include <bits/stdc++.h>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

//常量
const int N = 26;
const int MAX = 2 * N - 1;

//结构体
struct Node
{
    int weight;
    int parent;
    int left;
    int right;
    char ch;
};

//全局变量
Node tree[MAX];

//函数声明
void initTree();                        //初始化哈夫曼树
int findMin(int end, int excluded);     //寻找最小权值节点
void mergeNodes(int p, int l, int r);   //构建节点关系
void buildHuffmanTree();                //构建哈夫曼树
void generateCodes(char codes[N][N]);   //生成哈夫曼编码
bool decode(const string& bits);        //解码哈夫曼编码

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // 让弹出的 Windows 控制台按 UTF-8 显示输出
#endif

    initTree();
    buildHuffmanTree();

    cout << "根节点权值: " << tree[MAX - 1].weight << endl;
        
    char codes[N][N];
    generateCodes(codes);

    for (int i = 0; i < N; i++)
    {
        cout << char('A' + i) << " : " << codes[i] << endl;
    }


    string text;
    cout << "请输入一串大写英文字母：";
    if (!getline(cin, text) || text.empty())
    {
        cout << "请输入至少一个大写英文字母。\n";
        return 1;
    }

    string encoded;
    for (char ch : text)
    {
        if (ch < 'A' || ch > 'Z')
        {
            cout << "输入无效，只能输入 A～Z。\n";
            return 1;
        }

        encoded += codes[ch - 'A'];
    }

    cout << "哈夫曼编码：" << encoded;

    return 0;
}

void initTree()
{
    // 1. 初始化全部 51 个节点
    for (int i = 0; i < MAX; i++)
    {
        tree[i].weight = 0;
        tree[i].parent = -1;
        tree[i].left = -1;
        tree[i].right = -1;
        tree[i].ch = '\0';
    }

    // 2. 定义 26 个英文字母的频率
    int frequency[N] =
    {
        817, 149, 278, 425, 1270, 223, 202,
        609, 697, 15, 77, 403, 241, 675,
        751, 193, 10, 599, 633, 906, 276,
        98, 236, 15, 197, 7
    };

    // 3. 将频率和字母存入前 26 个节点
    for (int i = 0; i < N; i++)
    {
        tree[i].weight = frequency[i];
        tree[i].ch = 'A' + i;
    }
}

//寻找最小权值节点
int findMin(int end, int excluded)
{
    int minIndex = -1;

    for (int i = 0; i < end; i++)
    {
        if (tree[i].parent == -1 && i != excluded)
        {
            if (minIndex == -1 ||
                tree[i].weight < tree[minIndex].weight)
            {
                minIndex = i;
            }
        }
    }

    return minIndex;
}

// 合并两个节点
void mergeNodes(int p, int l, int r)
{
    // 新节点的权值等于两个孩子的权值之和
    tree[p].weight = tree[l].weight + tree[r].weight;

    // 建立父节点和左右孩子的关系
    tree[p].left = l;
    tree[p].right = r;

    // 更新两个孩子的父节点
    tree[l].parent = p;
    tree[r].parent = p;
}


// 构建哈夫曼树
void buildHuffmanTree()
{
    for (int i = N; i < MAX; i++)
    {
        int first = findMin(i, -1);
        int second = findMin(i, first);

        // 检查是否成功找到两个节点
        if (first == -1 || second == -1)
        {
            cout << "构建失败！" << endl;
            return;
        }

        mergeNodes(i, first, second);
    }
}

// 生成哈夫曼编码
void generateCodes(char codes[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            codes[i][j] = '\0';
        }
    }

    //遍历
    for(int i = 0; i < N; i++)
    {
        int current = i;
        int count = 0;
        while (tree[current].parent != -1)
        {
            int parent = tree[current].parent;
            if (tree[parent].left == current)
            {
                codes[i][count++] = '0';
                // 相当于
                // codes[i][count] = '0';
                // count++;
            }
            else
            {
                codes[i][count++] = '1';
            }
            current = parent;
        }

        // 反转编码
        for (int j = 0; j < count / 2; j++)
        {
            swap(codes[i][j], codes[i][count - j - 1]);
        }

        // 添加字符串结束符
        codes[i][count] = '\0';
    }
}

bool decode(const string& bits)
{
    int current = MAX - 1; // 从根节点开始
    for (char bit : bits)
    {
        if (bit == '0')
        {
            current = tree[current].left;
        }
        else if (bit == '1')
        {
            current = tree[current].right;
        }
        else
        {
            cout << "无效的编码！" << endl;
            return false;
        }

        // 如果到达叶子节点，输出字符并返回根节点
        if (tree[current].left == -1 && tree[current].right == -1)
        {
            cout << tree[current].ch;
            current = MAX - 1; // 返回根节点
        }
    }

    return current == MAX - 1;
}