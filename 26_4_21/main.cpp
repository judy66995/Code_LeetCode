# include <iostream>
# include <vector>
# include <unordered_map>

using namespace std;

class Allocator{
private:
    vector<int> memory;// 模拟内存空间
    unordered_map<int, int> idSize; // 记账本：记录每个ID占了多大空间

public:
    Allocator(int n){
        memory.resize(n);// 初始化内存空间
    }
    
    int allocate(int size, int mID) {//从左到右扫描内存，找最左边的连续空闲块。
        int n = memory.size();// 内存总大小
        int cnt = 0 ;// 记录连续空闲块的数量
        int start = -1;// 记录连续空闲块的起始位置

        for(int i=0;i<n;i++){
            if(memory[i]==0){//0表示空闲
                cnt++;
                if(cnt==1){
                    start=i;//遇到第一次空闲，记录起始位置
                }
                //找到一块足够长的连续空块
                if(cnt==size){
                    //把这一块全记为mID
                    for(int i=start;i<start+size;i++){
                        memory[i]=mID;
                    }

                    idSize[mID] += size;//更新记账本，记录mID占了多大空间
                    return start;//返回起始位置
                }
            }else{
                //遇到已占用块，重置计数器和起始位置
                cnt=0;
                start=-1;
            }
        }
        return -1;//遍历完都没有找到足够长的连续空块，返回-1
    }
    // 释放内存
    int freeMemory(int mID) {
        if (!idSize.count(mID)) return 0;// 如果mID不存在，说明没有占用内存，直接返回0
        int count = idSize[mID]; // 直接拿总大小

        // 清空内存
        for (int& x : memory) {// &意思是：直接修改原来的内存,不是复制一份,所以改x = 0,真正的memory也会变
            if (x == mID) x = 0;
        }

        idSize.erase(mID); // 删除记录
        return count;
    }
};



int main(){
    Allocator alllcator(10);// 创建一个大小为10的内存分配器
    cout<<"null,";
    cout<<alllcator.allocate(1,1)<<",";//分配大小为1，mID为1的内存块，返回起始位置
    cout<<alllcator.allocate(1,2)<<",";//分配大小为1，mID为2的内存块，返回起始位置
    cout<<alllcator.allocate(1,3)<<",";//分配大小为1，mID为3的内存块，返回起始位置
    cout<<alllcator.freeMemory(2)<<",";//释放mID为2的内存块，返回释放块总数
    cout<<alllcator.allocate(3,4)<<",";
    cout<<alllcator.allocate(1,1)<<",";
    cout<<alllcator.allocate(1,1)<<",";
    cout<<alllcator.freeMemory(1)<<",";
    cout<<alllcator.allocate(10,2)<<",";
    cout<<alllcator.freeMemory(7)<<endl;
    return 0;
}