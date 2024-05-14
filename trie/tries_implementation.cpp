class TrieNode{
    public:
    TrieNode* children[26];
    
    int wordEnd = 0;
    int cntPrefix = 0;
    
    TrieNode(){
        for(int i = 0; i<26; i++){
            children[i] = NULL;
        }
    }
    
    bool containsKey(char ch){
        return (children[ch-'a'] != nullptr);
    }
    
    TrieNode* get(char ch){
        return children[ch-'a'];
    }
    
    void put(char ch, TrieNode* node){
        children[ch-'a'] = node;
    }
    
    void increaseEnd(){
        wordEnd++;
    }
    
    void increasePrefix(){
        cntPrefix++;
    }
    
    void deleteEnd(){
        wordEnd--;
    }
    
    void reducePrefix(){
        cntPrefix--;
    }
    
    int getEnd(){
        return wordEnd;
    }
    
    int getPrefix(){
        return cntPrefix;
    }
};


class Trie{
    TrieNode* root;
    public:

    Trie(){
        root = new TrieNode();
    }

    void insert(string &word){
        TrieNode* curr = root;
        
        for(int i = 0; i<word.size(); i++){
            if(!curr->containsKey(word[i]))
                curr->put(word[i], new TrieNode());
            curr = curr->get(word[i]);
            curr->increasePrefix();
        }
        
        curr->increaseEnd();
    }

    int countWordsEqualTo(string &word){
        TrieNode* curr = root;
        for(int i = 0; i<word.size(); i++){
            if(curr->containsKey(word[i])){
                curr = curr->get(word[i]);
            }else 
                return 0;
        }
        
       return curr->getEnd();
    }

    int countWordsStartingWith(string &word){
         TrieNode* curr = root;
        for(int i = 0; i<word.size(); i++){
            if(curr->containsKey(word[i])){
                curr = curr->get(word[i]);
            }else 
                return 0;
        }
        
        return curr->getPrefix();
    }

    void erase(string &word){
        TrieNode* curr = root;
        for(int i = 0; i<word.size(); i++){
            if(curr->containsKey(word[i])){
                curr = curr->get(word[i]);
                curr->reducePrefix();
            }else 
                return;
        }
        curr->deleteEnd();
    }
};
