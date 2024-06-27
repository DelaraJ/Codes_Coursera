trie build_trie(string & Text) {
  trie t;
  int last_index = 0;
  int TextLength = Text.size();
  t.push_back({});
  for(int i=0; i< TextLength; i++){
	int index = i;
    int x = 0; // root
    while(index<TextLength){
    // for(int j=i; j<TextLength; j++){
      auto it = t[x].find(Text[index]);
      if(it!=t[x].end()){
        x = (*it).second;
      }
      else{
        //make node
        while(index<TextLength){
          last_index++;
          t[x].insert({Text[index], last_index});
          t.push_back({});
          x= last_index;
          index++;
        }
        break;
      }
    }
  }
  return t;
}