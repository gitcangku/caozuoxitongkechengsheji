
//OPT---最佳置换算法
#if 1
//选择永不使用或者最长时间不被使用的页面进行置换
//每次操作完之后重置队列
// 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
//结果：缺页数：9   置换数：6   缺页率：45%
#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>//sort()头文件
using namespace std;

struct pages
{
    int value;
    int time;
};
bool GreaterSort(pages a, pages b)
{
    return (a.time > b.time);
}

int main()
{
    deque<pages>  dq;
    deque<pages>::iterator pos;
    int blockNum;//物理块数
    int pageNum;//访问页面个数
    int missPageNum = 0;//缺页数
    int pageLabel;//当前输入的页面标签
    vector<int> pageList;//页面访问序列

    cout << "****************** OPT ********************" << endl;

    cout << "请输入物理页框块数:" << endl;
    cin >> blockNum;

    cout << "\n请输入页面走向个数：" << endl;
    cin >> pageNum;

    cout << "\n请输入访问页面序列：" << endl;
    for (int i = 0; i < pageNum; i++)
    {
        cin >> pageLabel;
        pageList.push_back(pageLabel);
    }


    for (int i = 0; i < pageNum; i++)
    {
        if (dq.size() < blockNum)//存在多余页框
        {
            bool flag = false;
            for (pos = dq.begin(); pos != dq.end(); pos++)
            {
                if ((*pos).value == pageList[i])//存在元素和它相同
                {
                    flag = true;
                    break;
                }  //存在该元素
            }

            if (!flag) //不存在此元素
            {
                missPageNum++;//缺页数+1
                pages temp;
                temp.value = pageList[i];

                bool flag2 = false;
                for (int j = i + 1; j < pageNum; j++)
                {
                    if (pageList[j] == pageList[i])
                    {
                        flag2 = true;
                        temp.time = j - i;
                        break;
                    }
                }
                if (!flag2)
                    temp.time = pageNum;//如果后面序列没有出现，time设置为总访问页面个数
                dq.push_back(temp);
            }
        }
        else //不存在多余页框
        {
            bool flag = false;
            for (pos = dq.begin(); pos != dq.end(); pos++)
            {
                if ((*pos).value == pageList[i])
                {
                    flag = true;
                    break;
                }  //存在该元素
            }

            if (!flag) //不存在此元素 则置换time最大的项
            {
                missPageNum++;//缺页数+1
                // 按照time从大到小排序
                sort(dq.begin(), dq.end(), GreaterSort);
                int maxTime = dq.front().time;//第物理块中第一个页面的time
                dq.pop_front();//time值最大的出队列

                pages temp;
                temp.value = pageList[i];
                bool flag2 = false;

                for (int j = i + 1; j < pageNum; j++)
                {
                    if (pageList[j] == pageList[i])
                    {
                        flag2 = true;
                        temp.time = j - i;
                        break;
                    }
                }

                if (!flag2)
                    temp.time = pageNum;
                dq.push_back(temp);
            }
        }
        //每次之后重置
        cout << endl << "第" << i + 1 << "个页面进入,队列中的元素为：";
        for (pos = dq.begin(); pos != dq.end(); pos++)
        {
            cout << (*pos).value << "  ";
            int flag = false;
            for (int j = i + 1; j < pageNum; j++)
                if (pageList[j] == (*pos).value)
                {
                    flag = true;
                    (*pos).time = j - i;
                    break;
                }
            if (!flag)
                (*pos).time = pageNum;
            //cout << "<" << (*pos).value << "," << (*pos).time << ">   ";
        }
        cout << endl << endl;
    }
    cout << "OPT缺页次数为：" << missPageNum << endl;
    cout << "OPT页面置换次数：" << missPageNum - 3 << endl;
    cout << "OPT缺页中断率为：" << (double)missPageNum / pageNum * 100 << "%" << endl;
    system("pause");

}

#endif

//FIFO---先进先出
#if 0
// 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
//结果：缺页数：15   置换数：12   缺页率：75%
#include <deque>
#include <vector>
#include <iostream>
using namespace std;

int main()
{
	deque<int>  dq;//创建动态数组用于存放内存中的页面
	deque<int >::iterator pos;//迭代器，用于遍历deque中的元素
	int blockNum;//物理块数
	int pageNum;//访问页面个数
	vector<int> pageList;//页面访问序列
	int pageLabel;//当前输入的页面标签
	int missPageNum = 0;//缺页数
	int count = 0;//计数

	cout << "****************** FIFO ********************" << endl;

	cout << "请输入物理页框块数:" << endl;
	cin >> blockNum;

	cout << "\n请输入页面走向个数：" << endl;
	cin >> pageNum;

	cout << "\n请输入访问页面序列：" << endl;
	for (int i = 0; i < pageNum; i++)
	{
		cin >> pageLabel;
		pageList.push_back(pageLabel);
	}

	vector<int>::iterator pageIter;
	for (pageIter = pageList.begin(); pageIter != pageList.end(); pageIter++)
	{

		if (dq.size() < blockNum)//存在空余页框
		{
			bool flag = false;
			for (pos = dq.begin(); pos != dq.end(); pos++) //遍历队列 
			{
				if ((*pos) == *pageIter)
				{
					flag = true;
					break;
				}
			}

			if (!flag) //不存在此元素
			{
				missPageNum++;//缺页数+1
				dq.push_back(*pageIter);//放入队列 
			}

		}
		else //不存在多余页框
		{
			bool flag = false;
			for (pos = dq.begin(); pos != dq.end(); pos++)
			if ((*pos) == *pageIter)
			{
				flag = true;
				break;
			}  //存在该元素
			if (!flag) //不存在此元素 则置换最先进入的项 
			{
				missPageNum++;//缺页数+1
				dq.pop_front();//最先进入的出队列 
				dq.push_back(*pageIter);//进队列 
			}
		}

		//显示每次页面进入物理块中作业
		cout << endl << "第" << ++count << "个页面进入,队列中的元素为：";
		for (pos = dq.begin(); pos != dq.end(); pos++)
		{
			cout << *pos << "  ";
		}
		cout << endl << endl;
	}
	cout << "FIFO缺页次数：" << missPageNum << endl;
	cout << "FIFO页面置换次数：" << missPageNum - 3 << endl;
	cout << "FIFO缺页中断率：" << (double)missPageNum / pageNum * 100 << "%" << endl;
	system("pause");
}

#endif

//LRU---最近最久未使用
#if 0
////by liuhao
// 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
//结果：缺页数：12   置换数：9   缺页率：60%
#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>//sort()头文件
using namespace std;

struct pages
{
	int value; //值
	int time;  //时间
};
bool GreaterSort(pages a, pages b)
{
	return (a.time > b.time);
}

int main()
{
	deque<pages>  dq;
	deque<pages>::iterator pos;
	int blockNum;//物理块数
	int pageNum;//访问页面个数
	int missPageNum = 0;//缺页数
	int pageLabel;//当前输入的页面标签
	vector<int> pageList;//页面访问序列

	cout << "****************** LRU ********************" << endl;

	cout << "请输入物理页框块数:" << endl;
	cin >> blockNum;

	cout << "\n请输入页面走向个数：" << endl;
	cin >> pageNum;

	cout << "\n请输入访问页面序列：" << endl;
	for (int i = 0; i < pageNum; i++)
	{
		cin >> pageLabel;
		pageList.push_back(pageLabel);
	}


	for (int i = 0; i < pageNum; i++)
	{
		if (dq.size() < blockNum)//存在多余页框
		{
			bool flag = false;
			for (pos = dq.begin(); pos != dq.end(); pos++)
			{
				if ((*pos).value == pageList[i])//存在元素和它相同
				{
					flag = true;
					break;
				}  //存在该元素
			}

			if (!flag) //不存在此元素
			{
				missPageNum++;//缺页数+1
				pages temp;
				temp.value = pageList[i];
				temp.time = 0;
				dq.push_back(temp);
			}
		}
		else //不存在多余页框
		{
			bool flag = false;
			for (pos = dq.begin(); pos != dq.end(); pos++)
			{
				if ((*pos).value == pageList[i])
				{
					flag = true;
					break;
				}  //存在该元素
			}

			if (!flag) //不存在此元素
			{
				missPageNum++;//缺页数+1
				// 按照time从大到小排序
				sort(dq.begin(), dq.end(), GreaterSort);
				dq.pop_front();//time值最大的出队列

				pages temp;
				temp.value = pageList[i];
				temp.time = 0;
				dq.push_back(temp);
			}
		}
		//每次之后各对象的time
		cout << endl << "第" << i + 1 << "个页面进入,队列中的元素为：";
		for (pos = dq.begin(); pos != dq.end(); pos++)
		{
			cout << (*pos).value << "  ";
			for (int j = i; j >= 0; j--)
			{
				if (pageList[j] == (*pos).value)
				{
					(*pos).time = i - j;
					break;
				}
			}
			//cout << "<" << (*pos).value << "," << (*pos).time << ">   ";
		}
		cout << endl << endl;
	}
	cout << "LRU缺页次数为：" << missPageNum << endl;
	cout << "LRU页面置换次数：" << missPageNum - 3 << endl;
	cout << "LRU缺页中断率为：" << (double)missPageNum / pageNum * 100 << "%" << endl;
	system("pause");
}

#endif