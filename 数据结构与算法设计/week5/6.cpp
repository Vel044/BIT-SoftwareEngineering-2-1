#include <bits/stdc++.h>
using namespace std;

int numAthletes;
int maleAthleteAdvantage[21][21], femaleAthleteAdvantage[21][21];   //用于存放男性和女性运动员的竞赛优势
int maxAdvantageSum=INT_MIN;   //maxAdvantageSum代表男女双方竞赛优势的总和的最大值
int tempSum=0;   //tempSum为临时求和
int advantageData[21][21];   //advantageData[i][]用于存放男运动员 i 配对后的双方竞赛优势
int maxMaleAdvantage[21];   //记录每个男生匹配后可达到的最大双方竞赛优势
int femaleMatched[21];   //用于标记女运动员是否已匹配：femaleMatched[0]未匹配；femaleMatched[1]匹配

void dfs(int t)
{
    if(t>=numAthletes)   //t到达numAthletes之后，代表全部标记访问了,得到了最大值
    {
        maxAdvantageSum=max(maxAdvantageSum,tempSum);
        return ;
    }
    int pruningValue=0;   //剪枝函数：之前t个已匹配好的男女运动员的tempSum与之后的 t->numAthletes-1 个男匹配女的最大值加起来与已经得到的maxAdvantageSum比较，若前者<=maxAdvantageSum，剪枝
    for(int i=t;i<numAthletes;i++)   //求t及t之后男生匹配女生的最大值的和
        pruningValue+=maxMaleAdvantage[i];
    if(tempSum+pruningValue<maxAdvantageSum)   //若从第t组->第numAthletes组，当前搜索tempSum加上假设匹配后的最大值pruningValue，仍然小于maxAdvantageSum ，就需要剪枝了，则maxAdvantageSum为已经求得的最大值
        return ;
    for(int i=0;i<numAthletes;i++)   //若pruningValue>=maxAdvantageSum，要探索子树。从第t个男生开始匹配，找未匹配的女生
    {
        if(!femaleMatched[i])   //第 i 个女生未匹配
        {
            femaleMatched[i]=1;   //第 t 个男生匹配女生i
            tempSum+=advantageData[t][i];   //加上男生t与女生i的男女双方竞赛优势
            dfs(t+1);   //为第i+1个男生匹配
            femaleMatched[i]=0;   //若第 t 个男生匹配女生i得到的tempSum不大于maxAdvantageSum，则回溯
            tempSum-=advantageData[t][i];
        }
    }
}

int main()
{
    cin>>numAthletes;
    for(int i=0;i<numAthletes;i++)   //输入男运动员的竞赛优势
    {
        for(int j=0;j<numAthletes;j++)
            cin>>maleAthleteAdvantage[i][j];
    }
    for(int i=0;i<numAthletes;i++)   //输入女运动员的竞赛优势
    {
        for(int j=0;j<numAthletes;j++)
            cin>>femaleAthleteAdvantage[i][j];
    }
    for(int i=0;i<numAthletes;i++)
    {
        for(int j=0;j<numAthletes;j++)
        {
            advantageData[i][j]=maleAthleteAdvantage[i][j]*femaleAthleteAdvantage[j][i];   //对每个男生都求男女双方竞赛优势，则能得到i*j种结果（涵盖了P[i][j]*Q[j][i]与Q[i][j]*P[j][i]）
            maxMaleAdvantage[i]=max(maxMaleAdvantage[i],advantageData[i][j]);   //记录每个男生匹配后可达到的最大双方竞赛优势，用于后面的剪枝
        }

    }
    dfs(0);
    cout<<maxAdvantageSum<<endl;
    return 0;
}
