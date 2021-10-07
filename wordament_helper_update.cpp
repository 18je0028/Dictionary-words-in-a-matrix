
#include<bits/stdc++.h>

using namespace std;


set<string> foundWords;
string inputArray[5][5];

bool visit[5][5];
int dx[] = {-1 , -1 , 0 , 1 , 1 , 1 , 0 , -1};
int dy[] = {0 , 1 , 1 , 1 , 0 , -1 , -1 , -1};

int getIndex(char ch)
{
	return ch - 'a';
}



struct node
{

    bool Eow;
    node* arr[26];
    node()
    {
      Eow=false;
      for(int i=0;i<26;i++)
        arr[i]=nullptr;
    }

};


void insert(node* root,string& s)
{

    int n=s.size();

    node* temp = root;

    for(int i=0;i<n;i++){
        int id = getIndex(s[i]);
        if(temp->arr[id]==nullptr){
            node* newnode = new node();
            temp->arr[id] = newnode;
        }
        temp = temp->arr[id];
    }

    temp->Eow = true;

}


int IsPresent(node* root,string& s)
{

    int n=s.size();

    node* temp = root;

    for(int i=0;i<n;i++){
        int id = getIndex(s[i]);
        if(temp->arr[id]==nullptr){
            return 0;
        }
        temp = temp->arr[id];
    }

    if(temp->Eow) return 1;

}

void preProcess(node* root)
{
    int total_words;
	cout<<"Enter total dictionary words available"<<endl;
	cin>>total_words;

	cout<<"Enter all the dictionary words on a separate new line"<<endl;

	for(int i=0;i<total_words;i++){

        string word;
        cin>>word;

        insert(root,word);

	}

}


void reset()
{
	for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
        visit[i][j]=0;
}

void dfs(node* root,int i , int j , string word)
{
	visit[i][j] = true;

	int n = word.size();

	if(n>1){
        bool result = IsPresent(root,word);
        if(result){
            foundWords.insert(word);
        }
	}

	if(foundWords.size() > 50) return;

	for(int index=1;index<=8;index++)
	{
		int x = i + dx[index-1];
		int y = j + dy[index-1];

		if(x >= 1 && x <= 4 && y >= 1 && y <= 4 && visit[x][y] == false)
		dfs(root , x , y , word + inputArray[x][y]);
	}

	visit[i][j] = false;

}

bool comp(string a , string b)
{
	return a.size() > b.size();
}

int main()
{
    node* root = new node();

	preProcess(root);

	int code = 1;

	while(code)
	{

	    foundWords.clear();

	    cout<<endl;
	    cout<<"Enter the matrix puzzle"<<endl;

	    for(int i=1;i<5;i++)
            for(int j=1;j<5;j++)
             cin>>inputArray[i][j];

        for(int i=1;i<5;i++){
            for(int j=1;j<5;j++){
                reset();
                dfs(root , i , j , inputArray[i][j] );
            }
        }


		cout<<foundWords.size()<<endl;
		cout<<endl<<endl<<"printing words"<<endl;

		vector<string> result;

		for(auto word : foundWords)
            result.push_back(word);

        foundWords.clear();

		sort(result.begin() , result.end() , comp);

		for(string word : result)
		cout<<word<<endl , result.pop_back();

		cout<<"enter 0 for exit"<<endl;
		cin>>code;
	}

}

