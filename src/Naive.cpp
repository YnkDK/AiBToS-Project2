#include "Naive.h"

int Naive::run(Parser &parser) {

    size_t S = parser.n;
    vector<double> r(parser.n);
    vector<double> dkm;
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

                if(parser.unused_d(j) || i == j) continue;
                dim += parser.get_d(i,j);

            }

            r[i] = dim/(S-2);
        }
        size_t mini = (size_t) -1;
        size_t minj = (size_t) -1;
        double minnij = std::numeric_limits<double>::max();
        for(i=1;i<parser.n;i++){

            if(parser.unused_d(i)) continue;

            for(j=i;j<parser.n;j++){

                if(parser.unused_d(j) || i == j) continue;
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
        size_t minioffsetD =  parser.getOffsetD(mini);
        size_t minjoffsetD = parser.getOffsetD(minj);
        edge.neighbor = minioffsetD;
        edge.weight = (parser.get_d(mini,minj) + r[mini]- r[minj])/2;
        T[k].push_back(edge);
        //create edge between mini and k
        edge.neighbor = k;
        T[minioffsetD].push_back(edge);

        //create edge between k and minj
        edge.neighbor = minjoffsetD;
        edge.weight = (parser.get_d(mini,minj) + r[minj]- r[mini])/2;
        T[k].push_back(edge);
        //create edge between minj and k
        edge.neighbor = k;
        T[minjoffsetD].push_back(edge);
        /*
         *
         * step 4
         *
         */

        dkm.resize(k);
        for(i=0;i<k;i++){

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

        for(i=0;i<k;i++){
            if(parser.unused_d(i)) continue;
            parser.set_d(k,i,dkm[i]);
            parser.set_d(i,k,dkm[i]);
        }

        S--;

    }

    size_t i,j,m;
    i = j = m = (size_t)-1;

    for(size_t x = 0; x < parser.n; x++){
        if(!parser.unused_d(x)){

            if(i == (size_t)-1) i = x;
            else if(j == (size_t)-1) j = x;
            else{
                m = x;
                break;
            }
        }
    }

    size_t v = parser.getNextId();

    /*
        *
        * final step
        *
        */

    i = parser.getOffsetD(i);
    j = parser.getOffsetD(j);
    m = parser.getOffsetD(m);

    Parser::Edge edge;
    //create edge between v and i
    edge.neighbor = i;
    edge.weight = (parser.get_d(i,j) + parser.get_d(i,m)-parser.get_d(j,m))/2;
    T[v].push_back(edge);
    edge.neighbor = v;
    T[i].push_back(edge);

    //create edge between v and j
    edge.neighbor = j;
    edge.weight = (parser.get_d(i,j) + parser.get_d(j,m)-parser.get_d(i,m))/2;
    T[v].push_back(edge);
    edge.neighbor = v;
    T[j].push_back(edge);

    //create edge between v and m
    edge.neighbor = m;
    edge.weight = (parser.get_d(i,m) + parser.get_d(j,m)-parser.get_d(i,j))/2;
    T[v].push_back(edge);
    edge.neighbor = v;
    T[m].push_back(edge);

    return EXIT_SUCCESS;
}
