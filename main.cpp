#pragma GCC optimize("Ofast")
#include<cstdio>
#include<algorithm>
using namespace std;
#define REP(i, n) \
    for(int i=0; i<n; i++)
int M;

struct Node {
	int point[4], upper_bound[4];
    Node *left, *right;
    Node(const int (&point)[4]){
        REP(i, M)
            this->point[i] = upper_bound[i] = point[i];
        left = right = NULL;
    }
    ~Node(){
        delete left;
        delete right;
    }
};

Node* insert(Node *root, const int (&point)[4], int discriminator){
    if(!root)
        return new Node(point);
    REP(i, M)
        root->upper_bound[i] = max(root->upper_bound[i], point[i]);
    discriminator %= M;
    if(point[discriminator] < root->point[discriminator])
        root->left = insert(root->left, point, discriminator + 1);
    else
        root->right = insert(root->right, point, discriminator + 1);
    return root; 
}

bool dominated(const int (&point1)[4], const int (&point2)[4]){
    REP(i, M)
        if(point1[i] > point2[i])
            return false;
    return true;
}

bool dominated(const int (&point)[4], Node *root){
    if(dominated(point, root->point))
        return true;
    if(root->left && dominated(point, root->left->upper_bound))
        if(dominated(point, root->left))
            return true;
    if(root->right && dominated(point, root->right->upper_bound))
        if(dominated(point, root->right))
            return true;
    return false;
}

int main(){
    int T;
    scanf("%d", &T);
    REP(i, T){
        int N;
        scanf("%d%d", &N, &M);
        if(M == 1){
            int temp;
            while(N--)
                scanf("%d", &temp);
            printf("Case #%d: 1\n", i+1);
        }else if(M == 2){
            pair<int, int> points[N];
            REP(j, N)
                scanf("%d%d", &points[j].first, &points[j].second);
            sort(points, points + N);
            int ans = 1, thres = points[--N].second;
            while(N--)
                if(points[N].second > thres){
                    thres = points[N].second;
                    ans++;
                }
            printf("Case #%d: %d\n", i+1, ans);
        }else{
            int points[N][4], ans = 1;
            REP(j, M)
                scanf("%d", &points[0][j]);
            Node *root = new Node(points[0]);
            while(--N){
                int point[4];
                REP(j, M)
                    scanf("%d", &point[j]);
                if(!dominated(point, root)){
                    insert(root, point, 0);
                    copy(point, point+M, points[ans++]);
                }
            }
            delete root;
            int index = ans;
            root = new Node(points[--index]);
            while(index--)
                if(dominated(points[index], root))
                    ans--;
                else
                    insert(root, points[index], 0);
            delete root;
            printf("Case #%d: %d\n", i+1, ans);
        }
    }
    return 0;
}