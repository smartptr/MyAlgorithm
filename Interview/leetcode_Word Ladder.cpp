class Solution {
public:
    int bfs(string s, string e, unordered_set<string >& data){
        queue<string> que;
        int n = mp.size();
        map<string, int> mp;
        que.push(s);
        mp[s] = 0;
        while(!que.empty()){
            string p = que.front();
            if(p == e) return mp[p];
            que.pop();
            for(int i = 0; i < p.length(); ++i){
                for(char c = 'a'; c <= 'z'; ++c){
                    string s = p;
                    s[i] = c;
                    if(data.find(s) != data.end()){
                        if(mp.find(s) == mp.end() ||mp[s] > mp[p] + 1){
                            que.push(s);
                            mp[s] = mp[p] + 1;
                        }
                    }
                }
            }
        }
        return -1;
    }
    int ladderLength(string start, string end, unordered_set<string> &dict) {
        return bfs(start, end, dict) + 1;
    }
};
