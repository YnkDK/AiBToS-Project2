#include "Naive.h"

int Naive::run(Parser &parser) {
    
    size_t S = parser.n;
    vector<double> r(parser.n);
    
    T.resize(2*parser.n);
    
    while(S > 3){
        
        size_t i,j;
        /*
         * step 1
         * 
         */
        for(i=0;i<parser.n;i++){
       
            if(parser.unused_d(i)) continue;
            double dim = 0.0;
            for(j=0;j<parser.n;j++){
            
                if(parser.unused_d(j)) continue;
                
                dim += parser.get_d(i,j);
            
            }
            
            r[i] = dim/(S-2);
        }
        
        size_t mini = -1;
        size_t minj = -1;
        double minnij = std::numeric_limits<double>::max();
        for(i=0;i<parser.n;i++){
            
            if(parser.unused_d(i)) continue;
            
            for(j=0;j<parser.n;j++){
            
                if(parser.unused_d(j)) continue;
                
                double nij = parser.get_d(i,j)-r[i]-r[j];
                if(nij < minnij){
                    minnij = nij;
                    mini = i;
                    minj = j;
                }
                
            }
            
        }
        
        /*
         * 
         * step 2
         * 
         */
        
        size_t k = parser.getNextId();
        
        /*
         * 
         * step 3
         * 
         */
        
        Parser::Edge edge;
        
        //create edge between k and mini
        edge.neighbor = mini;
        edge.weight = (parser.get_d(mini,minj) + r[mini]- r[minj])/2;
        T[k].push_back(edge);
        //create edge between mini and k
        edge.neighbor = k;
        T[mini].push_back(edge);
        
        //create edge between k and minj
        edge.neighbor = minj;
        edge.weight = (parser.get_d(mini,minj) + r[minj]- r[mini])/2;
        T[k].push_back(edge);
        //create edge between minj and k
        edge.neighbor = k;
        T[minj].push_back(edge);
        
        /*
         * 
         * step 4
         * 
         */
        
        vector<double> dkm(parser.getNextId()-1);
        
        for(i=0;i<dkm.size();i++){
        
            if(parser.unused_d(i)) continue;
            
            dkm[i] = (parser.get_d(mini,i)+parser.get_d(minj,i)-parser.get_d(mini,minj))/2;
        
        }
        
        /*
         * 
         * step 5
         * 
         */
        parser.delete_d(mini);
        parser.delete_d(minj);
        
        parser.add_node();
        
        for(i=0;i<dkm.size();i++){
            if(parser.unused_d(i)) continue;
            parser.set_d(k,i,dkm[i]);
        }
        
    }
    
    
    
    
    
    return EXIT_SUCCESS;
}
