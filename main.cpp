#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <istream>
#include <locale>
#include <algorithm>
#include <vector>
#include <cmath>
#include <time.h>
#include <list>
#define tabuLoops 7
#define geneticLoops 2
#define randArraySize 1000
using namespace std;

class knapsackProblem
{
private:
    string investment;
    double cost;
    double profit;
    int jobs;
public:
    knapsackProblem(){investment="0"; cost=0.0; profit=0.0; jobs=0;} //CONSTUCTORS
    knapsackProblem(string in_investment, double in_cost, int in_jobs,double in_profit){investment=in_investment; cost=in_cost; profit=in_profit; jobs=in_jobs;}

    string getInvestment(){return investment;} //GET FUNCS
    double getCost(){return cost;}
    double getProfit(){return profit;}
    int getJobs(){return jobs;}
};

double fRand(double fMin, double fMax) //KANE RAND DEKADIKOUS ARITHMOUS
    {
        struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
    }

bool isTabu(int ind,string *a, string from, string to){ // TRUE IF EPENDISEIS EINAI STIN TABU
    for(int i=0;i<ind;i+=2){
        if((a[i]==from) && (a[i+1]==to))
            return true;
    }
            return false;
}  

int main()
{
    ofstream simpleOutfile("simpleOutput.txt");
    ofstream detailedOutfile("detailedOutput.txt");
    knapsackProblem knapsack[50]; //CLASS OBJECT
    string in_investment; double in_cost; double in_profit; int in_jobs; //CLASS MEMBERS

    //OPEN FILE
    fstream in_file;
    in_file.open("askisi3.txt");
    if(!in_file.is_open()) {detailedOutfile<<"Could not open file!"; exit(1);}

    int i = 0; string ch; int ind;
	getline(in_file, ch);

        while(!in_file.eof()){
            in_file>>in_investment>>in_cost>>in_jobs>>in_profit;
            knapsack[i]=knapsackProblem(in_investment,in_cost,in_jobs,in_profit);
            i++;
        }
    ind=i-1;
    in_file.close();
    int numOfInvest=ind;
    //END OPEN FILE

    vector<string> ainvestment; //ARXIKOI PINAKES
    vector<double> acost;
    vector<double> aprofit;
    vector<int> athseis;
    ainvestment.clear();
    acost.clear();
    aprofit.clear();
    athseis.clear();

    for(i=0;i<ind;i++){ //ARXIKOPOIISI
        ainvestment.push_back(knapsack[i].getInvestment());
        acost.push_back(knapsack[i].getCost());
        athseis.push_back(knapsack[i].getJobs());
        aprofit.push_back(knapsack[i].getProfit());
    }

    for(i=0;i<ind;i++)
        simpleOutfile<<ainvestment[i]<<"   "<<acost[i]<<"   "<<athseis[i]<<"   "<<aprofit[i]<<endl;
    for(i=0;i<ind;i++)
        detailedOutfile<<ainvestment[i]<<"   "<<acost[i]<<"   "<<athseis[i]<<"   "<<aprofit[i]<<endl;

    //CONSTRUCTIVE------------------------------------------------------------------------------------------------------------------------------------
    vector<double> randArray; //PINAKAS RANDOM DEKADIKON ARITHMON
    for(i=0;i<randArraySize;i++)
        randArray.push_back(fRand(0,1));

    vector<string> solInvestment; //PINAKES SOLUTION
    vector<double> solCost;
    vector<double> solProfit;
    vector<int> solJobs;
    solInvestment.clear();
    solCost.clear();
    solProfit.clear();
    solJobs.clear();
    vector<string> restInvestment; //PINAKES REST
    vector<double> restCost;
    vector<double> restProfit;
    vector<int> restJobs;
    restInvestment.clear();
    restCost.clear();
    restProfit.clear();
    restJobs.clear();

    double costCAP=220.0; int jobsCAP=500; //PROYPOTHESEIS CONSTRUCTIVE

    int rand_ind=0; //INDICATOR TOU PINAKA RAND

    double goesIn=1.0; //POIA METOXI MPAINEI STIN ARXIKI LYSI

    int solind=0; //INDICATOR TOU PINAKA S

    double sumCost=0.0; double sumJobs=0; double zCurrent=0.0;

    for(i=0;i<numOfInvest;i++){
        goesIn=1.0;
        while(goesIn<=ind){ //POIA METOXI 8A MPEI STIN S APO TIS ARXIKES
            if((randArray[rand_ind]<(goesIn/(ind * 1.0))) && (sumCost+acost[goesIn-1]<costCAP)) {
                solInvestment.push_back(ainvestment[goesIn-1]); 
                solCost.push_back(acost[goesIn-1]);
                solJobs.push_back(athseis[goesIn-1]);
                solProfit.push_back(aprofit[goesIn-1]);

                ainvestment.erase(ainvestment.begin()+goesIn-1);
                acost.erase(acost.begin()+goesIn-1);
                athseis.erase(athseis.begin()+goesIn-1);
                aprofit.erase(aprofit.begin()+goesIn-1);

                sumCost+=solCost[solind];
                sumJobs+=solJobs[solind];
                zCurrent+=solProfit[solind];
                rand_ind++; 
                ind--;
                solind++;
                break;
            }
            else goesIn++;
        }
        if((sumCost>costCAP) && (sumJobs<jobsCAP)){ //AN OI THESEIS DEN EINAI ARKETES TREKS TO AP TIN ARXI
            sumCost=0.0;
            sumJobs=0;
            ainvestment.clear();
            acost.clear();
            aprofit.clear();
            athseis.clear();

            for(i=0;i<ind;i++){
                ainvestment.push_back(knapsack[i].getInvestment());
                acost.push_back(knapsack[i].getCost());
                athseis.push_back(knapsack[i].getJobs());
                aprofit.push_back(knapsack[i].getProfit());
            }
        }
    } //TELOS DIMIOURGIAS 1HS LISIS

    simpleOutfile<<endl<<"Constructive:"<<endl<<"S0: ";
    for(i=0;i<solind;i++)
    simpleOutfile<<solInvestment[i]<<" ";
    simpleOutfile<<endl;
    detailedOutfile<<endl<<"Constructive:"<<endl<<"S0: ";
    for(i=0;i<solind;i++)
    detailedOutfile<<solInvestment[i]<<" ";
    detailedOutfile<<endl;

    int restind; //INDICATOR TOU PINAKA TON YPOLOIPON
    restind=ainvestment.size();

    int j;

    for(j=0;j<restind;j++){ 
        restInvestment.push_back(ainvestment[j]);
        restCost.push_back(acost[j]);
        restJobs.push_back(athseis[j]);
        restProfit.push_back(aprofit[j]);
    }
    ainvestment.clear();
    acost.clear();
    athseis.clear();
    aprofit.clear();

    simpleOutfile<<"Rest: ";
    for(j=0;j<restind;j++)
    simpleOutfile<<restInvestment[j]<<" ";
    simpleOutfile<<endl;    
    
    simpleOutfile<<"Total Cost= "<<sumCost<<" Jobs= "<<sumJobs<<" zCurrent= "<<zCurrent<<endl<<endl; //SHOW TOTAL COST KAI THESEIS

    simpleOutfile<<"Tabu:"<<endl;
    detailedOutfile<<"Rest: ";
    for(j=0;j<restind;j++)
    detailedOutfile<<restInvestment[j]<<" ";
    detailedOutfile<<endl;    
    
    detailedOutfile<<"Total Cost= "<<sumCost<<" Jobs= "<<sumJobs<<" zCurrent= "<<zCurrent<<endl<<endl; //SHOW TOTAL COST KAI THESEIS

    detailedOutfile<<"Tabu:"<<endl;

    //END CONSTRUCTIVE--------------------------------------------------------------------------------------------------------------------------------

    int parentNumber=6; //POSES LYSEIS 8A PARW NA TIS VALW STON GENETIKO

    double bestMin=0.0; //MIN VALUE GIA NA DW AN 8A MPEI I TREXOUSA LYSI STIN BESTSCORE I OXI

    int bestind=0; //INDICATOR TOU BESTSCORE

    vector<double> bestScore; //TA zCURRENT TWN 6 KALYTERWN LYSEWN
    bestScore.clear();
    for(i=0;i<parentNumber;i++)
        bestScore.push_back(0.0);

    int tabuSize=6;
    
    string** bestSolutions=new string* [parentNumber]; //DYNAMIKOS 2D ME TIS METOXES TWN 6 KALYTERWN LYSEWN
    for(i=0;i<parentNumber;i++)
        bestSolutions[i]=new string[solind];

    cout<<"For profit optimization press 1!"<<endl;
    cout<<"For jobs optimization press 2!"<<endl;
    int erwtisi;
    cin>>erwtisi;

    if(erwtisi==1)
    {
        detailedOutfile<<"MAXIMIZE PROFIT!"<<endl;
    //TABU SEARCH---------------------------------------------------------------------------------------------------------------------------
    double getsOut=0; //POIA METOXI VGAINEI
    double zBest=zCurrent; //BEST PROFIT

    string loopBestInvestment; //KALYTERES TIMES TIS TREXOUSAS LOOPAS
    double loopBestCost;
    double loopBestProfit;
    int loopBestJobs;

    string investmentOut; //POIA METOXI ONTOS VGAINEI (DILADI I LYSI TIS LOOPAS EINAI KALYTERI TIS PROIGOUMENIS)

    vector<string> bestInvestment; //BEST TIMES GIA NA TIS TYPWSW STO TELOS
    double bestCost=sumCost;
    int bestJobs=sumJobs;

    string tabuList[6]={"0"}; int tabuind=0; //ARXIKOPOIISI TABU LISTAS (3 ZEYGARIA) KAI TABU INDICATOR (GIA TIN LISTA)

    int diversind=0; //DIVERSIFICATION PARAMETER (AN DEN VREIS LYSI GIA N LOOPES PANE ALLOU)

    vector<string> recoverInvestment; //POU NA PAEI META TO DIVERSIFICATION
    vector<double> recoverCost;
    vector<int> recoverJobs;
    vector<double> recoverProfit;
    for(i=0;i<solind;i++){
        recoverInvestment.push_back(solInvestment[i]);
        recoverCost.push_back(solCost[i]);
        recoverProfit.push_back(solProfit[i]);
        recoverJobs.push_back(solJobs[i]);
    }

    string tempInvestment; //KRATA TIN TIMI GIA LIGI WRA (TEMP)
    double tempCost;
    double tempProfit;
    int tempThseis;

    double zAverage=0.0;
    double averageInd=0.0;

    for(i=0;i<solind;i++)
        bestInvestment.push_back(solInvestment[i]);

    int restGoesIn;
    double loopMaxProfit;

    for(int loops=0;loops<tabuLoops;loops++){ //TABU LOOPS-----------------------------------------------------
        detailedOutfile<<"loooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooop: "<<loops+1<<endl;

        for(i=0;i<solind;i++) detailedOutfile<<solInvestment[i]<<" ";
        detailedOutfile<<endl;

        averageInd=0.0;
        zAverage=0.0;
        getsOut=1.0;

        while(getsOut<=solind){ //POIA EPENDISI TOU S 8A VGEI
            if(randArray[rand_ind]<(getsOut/(solind*1.0))) {

                detailedOutfile<<"rand= "<<randArray[rand_ind]<<" vgainei to "<<solInvestment[getsOut-1]<<endl<<endl;

                investmentOut=solInvestment[getsOut-1];
                tempInvestment=solInvestment[getsOut-1];
                tempCost=solCost[getsOut-1];
                tempProfit=solProfit[getsOut-1];
                tempThseis=solJobs[getsOut-1];
                rand_ind++;
                break;
            }
            else getsOut++;
        }

        loopBestInvestment=tempInvestment; //ARXIKOPOIISI LOOPBEST
        loopBestCost=tempCost;
        loopBestProfit=tempProfit;
        loopBestJobs=tempThseis;


        loopMaxProfit=0.0;

        for(int j=0;j<restind;j++){ //VALE MIA-MIA TIS "REST" STIN 8ESI TOU "VGAINEI" KAI VRES zBEST KLP

            solInvestment[getsOut-1]=restInvestment[j]; //ANTIKATASTASI AYTOU POU VGAINEI ME TO REST
            solCost[getsOut-1]=restCost[j];
            solJobs[getsOut-1]=restJobs[j];
            solProfit[getsOut-1]=restProfit[j];
            sumCost=0.0; sumJobs=0.0; zCurrent=0.0;

            for(int k=0;k<solind;k++){ //YPOLOGISE KAINOURIA zCURRENT KLP
                sumCost+=solCost[k];
                sumJobs+=solJobs[k];
                zCurrent+=solProfit[k];
            }

            if((!isTabu(tabuSize,tabuList,tempInvestment,restInvestment[j])) || (zCurrent>zBest)){ //TABU LISTA && ASPIRATION CRITERION

                detailedOutfile<<"Out  "<<tempInvestment<<" In  "<<restInvestment[j]<<"   zCurrent=   "<<zCurrent<<" Cost= "<<sumCost;
                if((sumJobs>jobsCAP) && (sumCost<costCAP)){

                    if(zCurrent>loopMaxProfit){
                        restGoesIn=j;
                        loopMaxProfit=zCurrent;
                        loopBestInvestment=solInvestment[getsOut-1];
                        loopBestCost=solCost[getsOut-1];
                        loopBestProfit=solProfit[getsOut-1];
                        loopBestJobs=solJobs[getsOut-1];
                    }

                    if((zCurrent>zBest)){   //AN zCURRENT KALYTERO TOTE KANE TIN LYSI KALYTERI

                        loopBestInvestment=solInvestment[getsOut-1];
                        loopBestCost=solCost[getsOut-1];
                        loopBestProfit=solProfit[getsOut-1];
                        loopBestJobs=solJobs[getsOut-1];

                        restGoesIn=j; //TO KLEIDI GIA TO POIA 8A VGEI

                        zBest=zCurrent;
                        loopMaxProfit=zCurrent;
                        detailedOutfile<<" "<<loopBestInvestment<<" zBest= "<<zBest<<"    ";
                        bestCost=sumCost;
                        bestJobs=sumJobs;
                        bestInvestment[getsOut-1]=loopBestInvestment;

                        detailedOutfile<<" ";
                        for(int tmp=0;tmp<solind;tmp++) detailedOutfile<<solInvestment[tmp]<<" ";
                        detailedOutfile<<" ";

                        diversind=0;
                        recoverInvestment.clear();
                        recoverCost.clear();
                        recoverJobs.clear();
                        recoverProfit.clear();

                        for(int recover=0;recover<solind;recover++){
                            recoverInvestment.push_back(solInvestment[recover]);
                            recoverCost.push_back(solCost[recover]);
                            recoverJobs.push_back(solJobs[recover]);
                            recoverProfit.push_back(solProfit[recover]);
                        }
                    }

                    detailedOutfile<<endl;
                    bestind=0;
                    if(zCurrent>bestMin){ //AN zCURRENT MESA STIS TOP 6 VALTIN STON BESTSCORE
                        while(bestind<parentNumber){
                            if(bestScore[bestind]==bestMin){
                                bestScore[bestind]=zCurrent;
                            for(i=0;i<solind;i++) //POIES EPENDYSEIS APOTELOUN TIN CURRENT LYSI
                                bestSolutions[bestind][i]=solInvestment[i];
                            break;
                            }
                            else bestind++;
                        }

                        detailedOutfile<<"zCurrent= "<<zCurrent<<endl<<"bestScore: ";
                        for(i=0;i<6;i++)detailedOutfile<<bestScore[i]<<" ";
                        detailedOutfile<<endl<<"bestMin= "<<bestMin;
                            
                    }
                    bestMin=100;
                    for(bestind=0;bestind<parentNumber;bestind++) //ANANEWSE TO BESTMIN
                        if(bestScore[bestind]<=bestMin)
                            bestMin=bestScore[bestind];
                }
                detailedOutfile<<endl;
            }
            else detailedOutfile<<"WARNING: Move From "<<tempInvestment<<" To "<<restInvestment[j]<<" is a TABU move!"<<endl;

            if((sumJobs>jobsCAP) && (sumCost<costCAP)){ //zAVERAGE++
                zAverage+=zCurrent; 
                averageInd++;
                }
        }

        if(averageInd>0){ //VRES zAVERAGE GIA NA DEIS AN 8A AYKSISEIS TON DIVERSIND
            zAverage=zAverage/averageInd;
            detailedOutfile<<"zAve= "<<zAverage<<endl;
            }

        if(loopBestInvestment!=investmentOut){ //EAN EGINE METATHESI SE AYTIN TIN LOOPA, ANANEWSE TIN TABU LISTA

            restInvestment[restGoesIn]=tempInvestment;
            restCost[restGoesIn]=tempCost;
            restProfit[restGoesIn]=tempProfit;
            restJobs[restGoesIn]=tempThseis;

            tabuList[tabuind]=loopBestInvestment;
            tabuList[tabuind+1]=investmentOut;
            tabuind+=2;

            if(tabuind==tabuSize)
                tabuind=0;

            detailedOutfile<<endl<<"TABU: ";
            for(i=0;i<6;i++)
                detailedOutfile<<tabuList[i]<<"   ";
            detailedOutfile<<endl;
        }

        solInvestment[getsOut-1]=loopBestInvestment; //VALE STIN 8ESI POU ELEIPE, TO KALYTERO POU VRIKES SE AYTIN TIN LOOPA
        solCost[getsOut-1]=loopBestCost;
        solJobs[getsOut-1]=loopBestJobs;
        solProfit[getsOut-1]=loopBestProfit;

        if(zAverage>=zBest*0.97){ //EINAI KALI I LYSI? (97% TIS ARXIKIS)
            diversind=0;
            recoverInvestment.clear();
            recoverCost.clear();
            recoverJobs.clear();
            recoverProfit.clear();
            }
        else diversind++;

        detailedOutfile<<"Divers: "<<diversind<<endl;
        if(diversind==4){ //AN GIA 3H FORA SYNEXOMENA DEN VRIKES KALI LYSI PANE PISW STIN TELEYTAIA KALI
            diversind=0;
           
            for(int recover=0;recover<solind;recover++){
                solInvestment[recover]=recoverInvestment[recover];
                solCost[recover]=recoverCost[recover];
                solProfit[recover]=recoverProfit[recover];
                solJobs[recover]=recoverJobs[recover];
            }
            detailedOutfile<<endl<<"Recover to ";
            for(i=0;i<solind;i++) detailedOutfile<<recoverInvestment[i]<<" ";
            detailedOutfile<<endl;
        }
    } //END TABU LOOP

    detailedOutfile<<endl<<"-----------------------------------------------------------"<<endl; //TYPWSE TA TELEYTAIA APOTELESMATA
        for(i=0;i<solind;i++){
            simpleOutfile<<bestInvestment[i]<<" ";
        }
        simpleOutfile<<endl<<"cost= "<<bestCost<<" jobs= "<<bestJobs<<" zBest= "<<zBest<<endl;
        simpleOutfile<<"Tabu= ";
        for(tabuind=0;tabuind<6;tabuind++)
            simpleOutfile<<tabuList[tabuind]<<"  ";

        simpleOutfile<<endl;
        for(i=0;i<solind;i++){
            detailedOutfile<<bestInvestment[i]<<" ";
        }
        detailedOutfile<<endl<<"cost= "<<bestCost<<" jobs= "<<bestJobs<<" zBest= "<<zBest<<endl;
        detailedOutfile<<"Tabu= ";
        for(tabuind=0;tabuind<6;tabuind++)
            detailedOutfile<<tabuList[tabuind]<<"  ";

        detailedOutfile<<endl;

    detailedOutfile<<endl<<"--------6 best solutions-----------"<<endl;
    for(bestind=0;bestind<parentNumber;bestind++){
            for(j=0;j<solind;j++){
                detailedOutfile<<bestSolutions[bestind][j]<<" ";
            }
        detailedOutfile<<" with value:"<<bestScore[bestind]<<endl;
    }
//GENETIC-----------------------------------------------------------------------------------------------------------------------------------------

    int** chromosomes=new int* [parentNumber]; //PINAKAS 2D ME TA XROMOSWMATA (0,1)
    for(i=0;i<numOfInvest;i++)
        chromosomes[i]=new int[numOfInvest];
    for(i=0;i<parentNumber;i++){
        for(j=0;j<numOfInvest;j++)
            chromosomes[i][j]=0;
    }
    
    int tmp;
    char char2string[4];
    for(j=0;j<4;j++)
        char2string[j]='e'; //VALE e STO TELOS TOU CHAR GIA INDICATOR AN 8A METRAEI KAI TO 2o PSIFIO
    
    for(i=0;i<parentNumber;i++){ //GEMISE TA XRWMOSWMATA ME 1 OPOU XREIAZETAI (1: H METOXI YPARXEI STIN LYSI , 0: I METOXI DEN YPARXEI)
        for(j=0;j<solind;j++){

            bestSolutions[i][j].copy(char2string, bestSolutions[i][j].size() + 1); //CHARACTER POU PAIRNEI TIN TIMI TOU STRING
            char2string[bestSolutions[i][j].size()] = '\0';
            bestSolutions[i][j]=char2string[1]; //VALE TON ARI8MO TIS EPENDISIS SE STRING
            if(char2string[2]!='e')
                bestSolutions[i][j].push_back(char2string[2]); //AN EINAI DIPSIFIOS VALE KAI TO 2o PSIFIO STO STRING
            tmp=stoi(bestSolutions[i][j]); //TEMP INT POU PAIRNEI TIN TIMI TOU STRING

            chromosomes[i][tmp-1]=1; //GEMISE TON PINAKA XRWMOSOMATA
        }
    }

    vector<int> chromInd;
    chromInd.clear();
    vector<double> geneticInit;
    geneticInit.clear();
    double tmpMax;
    int bestChild;

    double mut_value;
    int mut_chrom[14]={0};
    double mut_min=10000.0;

    for(int loops=0;loops<geneticLoops;loops++){ //GENETIC LOOPS--------------------------------
        ind=0; tmpMax=0.0; chromInd.clear(); geneticInit.clear();

        for(i=0;i<parentNumber;i++) //IDIOS ME TON BESTSCORE
            geneticInit.push_back(bestScore[i]);
        
        bestScore.clear();
    
        for(j=0;j<parentNumber;j++){ //TAKSINOMIS TIS 8ESEIS TOU PINAKA SE F8INOUSA TIMI
            tmpMax=0.0;
            for(i=0;i<parentNumber;i++){
                if(tmpMax<geneticInit[i]){
                    tmpMax=geneticInit[i];
                    ind=i;
                }
            }
            geneticInit[ind]=0.0;
            chromInd.push_back(ind);
        }

        for(int k=0;k<parentNumber;k++)
            chromInd[k]++;
        detailedOutfile<<"i seira: "; //ME POIA SEIRA 8A MPOUN TA ZEYGARIA
        for(int k=0;k<parentNumber;k++)
            detailedOutfile<<chromInd[k]<<" ";
        detailedOutfile <<endl;


        for(i=0;i<parentNumber;i+=2){ //EPILOGI GONEON - VGALE ZEYGARIA ME VASI TON RAND PINAKA
            detailedOutfile<<"Pair "<<(i+2)/2<<": "<<chromInd[i]<<" - "<<chromInd[i+1]<<endl;
            for(j=0;j<numOfInvest;j++){
                detailedOutfile<<chromosomes[chromInd[i]-1][j]<<" "; //GONEAS 1
            }
            detailedOutfile<<endl;
            for(j=0;j<numOfInvest;j++){
                detailedOutfile<<chromosomes[chromInd[i+1]-1][j]<<" "; //GONEAS 2
            }
            detailedOutfile<<endl;
        }

        ind=0;
        double splitPoint=1.0; //POU 8A KOPEI TO DNA GIA NA GINEI DIASTAVROSI
        vector<int> tmpChrom;
        tmpChrom.clear();
        mut_min=1000.0;
        
        int mut_ind;

        for(i=0;i<parentNumber;i+=2){ //GIA OLA TA ZEYGARIA
        splitPoint=1.0;
            while(splitPoint<=numOfInvest){ 
                if(randArray[rand_ind]>0.85)randArray[rand_ind]=0.5*randArray[rand_ind]; //AN VGALEIS MEGALO RAND MIKRINE TO
                if(randArray[rand_ind]<splitPoint/(numOfInvest * 1.0)){ //MOLIS VREIS TO SPLITPOINT KANE DIASTAVROSI
                    ind=0;
                    tmpChrom.clear();
                    for(tmp=splitPoint-1;tmp<numOfInvest;tmp++){ //PERNA TO DNA META TO SPLITPOINT STON ALLO GONEA KAI ANTISTROFA
                        tmpChrom.push_back(chromosomes[chromInd[i]-1][tmp]);
                        chromosomes[chromInd[i]-1][tmp]=chromosomes[chromInd[i+1]-1][tmp];
                        chromosomes[chromInd[i+1]-1][tmp]=tmpChrom[ind];
                        ind++;
                    }
                    rand_ind++;
                    break;
                }
                else splitPoint++;
            }
            //METALLAKSI
            mut_value=0.0;
            int k=0;
            while(k<numOfInvest){
                if(chromosomes[chromInd[i]-1][k]==1){
                    mut_value+=knapsack[k].getProfit();
                    k++;
                }
                else k++;
            }
            if(mut_value<mut_min){
                mut_min=mut_value;
                for(k=0;k<numOfInvest;k++)
                    mut_chrom[k]=chromosomes[chromInd[i]-1][k];
                mut_ind=chromInd[i]-1;
            }

            mut_value=0.0; k=0;
            while(k<numOfInvest){
                if(chromosomes[chromInd[i+1]-1][k]==1){
                    mut_value+=knapsack[k].getProfit();
                    k++;
                }
                else k++;
            }
            if(mut_value<mut_min){
                mut_min=mut_value;
                for(k=0;k<numOfInvest;k++)
                    mut_chrom[k]=chromosomes[chromInd[i+1]-1][k];
                mut_ind=chromInd[i+1]-1;
            }

            detailedOutfile<<endl<<"rand: "<<randArray[rand_ind-1]<<" splitPoint: "<<splitPoint<<endl<<endl;
        }
        
        detailedOutfile<<"child with value "<<mut_min<<" to be mutated, Chroms: ";
        for(int k=0;k<14;k++)
            detailedOutfile<<mut_chrom[k]<<" ";
        detailedOutfile<<endl;

        int mut_tmp;
        mut_tmp=rand()%numOfInvest;
        mut_chrom[mut_tmp]=abs(mut_chrom[mut_tmp]-1);
        mut_value=0.0;
        for(int k=0;k<numOfInvest;k++){
            if(mut_chrom[k]==1){
                mut_value+=knapsack[k].getProfit();
            }
        }

            for(int k=0;k<14;k++){
                chromosomes[mut_ind][k]=mut_chrom[k];
            }
            
        detailedOutfile<<"rand= "<<mut_tmp+1<<" ";
        detailedOutfile<<"mutated chiled new value: "<<mut_value<< " new chroms: ";

        for(int k=0;k<14;k++)
            detailedOutfile<<chromosomes[mut_ind][k]<<" ";
        detailedOutfile<<endl;

        for(i=0;i<parentNumber;i+=2){ //GIA OLA TA ZEYGARIA
            detailedOutfile<<"Pair "<<(i+2)/2<<": "<<chromInd[i]<<" - "<<chromInd[i+1]<<endl;
            for(j=0;j<numOfInvest;j++){
                detailedOutfile<<chromosomes[chromInd[i]-1][j]<<" "; //PAIDI 1
            }
            detailedOutfile<<endl;
            for(j=0;j<numOfInvest;j++){
                detailedOutfile<<chromosomes[chromInd[i+1]-1][j]<<" "; //PAIDI 2
            }
            detailedOutfile<<endl;
        }

        sumCost=0.0;
        zCurrent=0.0;
        zBest=0.0;
        bestCost=0.0;

        j=0;
        ind=0;
        for(i=0;i<parentNumber;i++){ //TYPWSE TA TELEYTAIA APOTELESMATA
            j=0;
            sumCost=0.0;
            zCurrent=0.0;
            while(j<numOfInvest){
                if(chromosomes[i][j]==1){
                    sumCost+=knapsack[j].getCost();
                    zCurrent+=knapsack[j].getProfit();
                    j++;
                }
                else j++;
            }
            bestScore.push_back(zCurrent);
            detailedOutfile<<"Child "<<i+1<<" cost: "<<sumCost<<" profit: "<<zCurrent<<endl;
            if((zCurrent>zBest) && (sumCost<costCAP)){
                zBest=zCurrent;
                bestCost=sumCost;
                bestChild=i+1;
            }
        }
    }
        simpleOutfile<<endl<<"Genetic:"<<endl;
        simpleOutfile<<"Best Child No: "<<bestChild<<" cost: "<<bestCost<<" profit "<<zBest<<endl;
        detailedOutfile<<endl<<"Genetic:"<<endl;
        detailedOutfile<<"Best Child No: "<<bestChild<<" cost: "<<bestCost<<" profit "<<zBest<<endl;
    //END-GENETIC-------------------------------------------------------------------------------------------------------------------------------------
    }
    if(erwtisi==2)
    {
        detailedOutfile<<"MAXIMIZE JOBS!"<<endl;
    //TABU SEARCH------------------------------------------------------------------------------------------------------------------------------
    double getsOut=0; //POIA METOXI VGAINEI
    double zBest=zCurrent; //BEST PROFIT
    double jobCurrent=sumJobs;
    double jobBest=sumJobs;

    string loopBestInvestment; //KALYTERES TIMES TIS TREXOUSAS LOOPAS
    double loopBestCost;
    double loopBestProfit;
    int loopBestJobs;

    string investmentOut; //POIA METOXI ONTOS VGAINEI (DILADI I LYSI TIS LOOPAS EINAI KALYTERI TIS PROIGOUMENIS)

    vector<string> bestInvestment; //BEST TIMES GIA NA TIS TYPWSW STO TELOS
    double bestCost;

    string tabuList[6]={"0"}; int tabuind=0; //ARXIKOPOIISI TABU LISTAS (3 ZEYGARIA) KAI TABU INDICATOR (GIA TIN LISTA)

    int diversind=0; //DIVERSIFICATION PARAMETER (AN DEN VREIS LYSI GIA N LOOPES PANE ALLOU)

    vector<string> recoverInvestment; //POU NA PAEI META TO DIVERSIFICATION
    vector<double> recoverCost;
    vector<int> recoverJobs;
    vector<double> recoverProfit;
    for(i=0;i<solind;i++){
        recoverInvestment.push_back(solInvestment[i]);
        recoverCost.push_back(solCost[i]);
        recoverProfit.push_back(solProfit[i]);
        recoverJobs.push_back(solJobs[i]);
    }

    string tempInvestment; //KRATA TIN TIMI GIA LIGI WRA (TEMP)
    double tempCost;
    double tempProfit;
    int tempThseis;

    double zAverage=0.0;
    double averageInd=0.0;

    for(i=0;i<solind;i++)
        bestInvestment.push_back(solInvestment[i]);

    int restGoesIn;
    double loopMaxJobs;

    for(int loops=0;loops<tabuLoops;loops++){ //TREKSE 7 FORES TON TABU
        detailedOutfile<<"loooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooop: "<<loops+1<<endl;

        for(i=0;i<solind;i++) detailedOutfile<<solInvestment[i]<<" ";
        detailedOutfile<<endl;

        averageInd=0.0;
        zAverage=0.0;
        getsOut=1.0;

        while(getsOut<=solind){ //POIA EPENDISI TOU S 8A VGEI
            if(randArray[rand_ind]<(getsOut/(solind*1.0))) {

                detailedOutfile<<"rand= "<<randArray[rand_ind]<<" vgainei to "<<solInvestment[getsOut-1]<<endl<<endl;

                investmentOut=solInvestment[getsOut-1];
                tempInvestment=solInvestment[getsOut-1];
                tempCost=solCost[getsOut-1];
                tempProfit=solProfit[getsOut-1];
                tempThseis=solJobs[getsOut-1];
                rand_ind++;
                break;
            }
            else getsOut++;
        }

        loopBestInvestment=tempInvestment; //ARXIKOPOIISI LOOPBEST
        loopBestCost=tempCost;
        loopBestProfit=tempProfit;
        loopBestJobs=tempThseis;

        loopMaxJobs=0.0;

        for(int j=0;j<restind;j++){ //VALE MIA-MIA TIS "REST" STIN 8ESI TOU "VGAINEI" KAI VRES zBEST KLP

            solInvestment[getsOut-1]=restInvestment[j]; //ANTIKATASTASI AYTOU POU VGAINEI ME TO REST
            solCost[getsOut-1]=restCost[j];
            solJobs[getsOut-1]=restJobs[j];
            solProfit[getsOut-1]=restProfit[j];
            sumCost=0.0; sumJobs=0.0; zCurrent=0.0; jobCurrent=0.0;

            for(int k=0;k<solind;k++){ //YPOLOGISE KAINOURIA zCURRENT KLP
                sumCost+=solCost[k];
                sumJobs+=solJobs[k];
                jobCurrent+=solJobs[k];
                zCurrent+=solProfit[k];
            }

            if((!isTabu(tabuSize,tabuList,tempInvestment,restInvestment[j])) || (jobCurrent>jobBest)){ //EAN I METATHESI DEN EINAI STIN TABU LISTA && ASPIRATION CRITERION

                detailedOutfile<<"Out  "<<tempInvestment<<" In  "<<restInvestment[j]<<"   Jobs=   "<<jobCurrent<<" Cost= "<<sumCost;
                if((sumJobs>jobsCAP) && (sumCost<costCAP)){

                    if(jobCurrent>loopMaxJobs){
                        restGoesIn=j;
                        loopMaxJobs=jobCurrent;
                        loopBestInvestment=solInvestment[getsOut-1];
                        loopBestCost=solCost[getsOut-1];
                        loopBestProfit=solProfit[getsOut-1];
                        loopBestJobs=solJobs[getsOut-1];
                    }                    

                    if((jobCurrent>jobBest)){   //AN jobCurrent KALYTERO TOTE KANE TIN LYSI KALYTERI
                        
                        loopBestInvestment=solInvestment[getsOut-1];
                        loopBestCost=solCost[getsOut-1];
                        loopBestProfit=solProfit[getsOut-1];
                        loopBestJobs=solJobs[getsOut-1];
                        restGoesIn=j;

                        jobBest=jobCurrent;
                        detailedOutfile<<" "<<loopBestInvestment<<" zBest= "<<jobBest<<"    ";
                        bestCost=sumCost;
                        zBest=zCurrent;
                        bestInvestment[getsOut-1]=loopBestInvestment;

                        detailedOutfile<<" ";
                        for(int tmp=0;tmp<solind;tmp++) detailedOutfile<<solInvestment[tmp]<<" ";
                        detailedOutfile<<" ";

                        diversind=0;
                        recoverInvestment.clear();
                        recoverCost.clear();
                        recoverJobs.clear();
                        recoverProfit.clear();

                        for(int recover=0;recover<solind;recover++){
                            recoverInvestment.push_back(solInvestment[recover]);
                            recoverCost.push_back(solCost[recover]);
                            recoverJobs.push_back(solJobs[recover]);
                            recoverProfit.push_back(solProfit[recover]);
                        }
                    }

                    detailedOutfile<<endl;
                }
                detailedOutfile<<endl;
            }
            else detailedOutfile<<"WARNING: Move From "<<tempInvestment<<" To "<<restInvestment[j]<<" is a TABU move!"<<endl;

            if((sumJobs>jobsCAP) && (sumCost<costCAP)){ //zAVERAGE++
                zAverage+=jobCurrent; 
                averageInd++;
                }
        }
        if(averageInd>0){ //VRES zAVERAGE GIA NA DEIS AN 8A AYKSISEIS TON DIVERSIND
            zAverage=zAverage/averageInd;
            detailedOutfile<<"zAve= "<<zAverage<<endl;
            }

        if(loopBestInvestment!=investmentOut){ //EAN ONTOS EGINE METATHESI SE AYTIN TIN LOOPA, ANANEWSE TIN TABU LISTA

            restInvestment[restGoesIn]=tempInvestment;
            restCost[restGoesIn]=tempCost;
            restProfit[restGoesIn]=tempProfit;
            restJobs[restGoesIn]=tempThseis;

            tabuList[tabuind]=loopBestInvestment;
            tabuList[tabuind+1]=investmentOut;
            tabuind+=2;

            if(tabuind==6)
                tabuind=0;

            detailedOutfile<<endl<<"TABU: ";
            for(i=0;i<6;i++)
                detailedOutfile<<tabuList[i]<<"   ";
            detailedOutfile<<endl;
        }

        solInvestment[getsOut-1]=loopBestInvestment; //VALE STIN 8ESI POU ELEIPE, TO KALYTERO POU VRIKES SE AYTIN TIN LOOPA
        solCost[getsOut-1]=loopBestCost;
        solJobs[getsOut-1]=loopBestJobs;
        solProfit[getsOut-1]=loopBestProfit;

        if(zAverage>=jobBest*0.95){ //EINAI KALI I LYSI? (97% TIS ARXIKIS)
            diversind=0;
            recoverInvestment.clear();
            recoverCost.clear();
            recoverJobs.clear();
            recoverProfit.clear();
            }
        else diversind++;

        detailedOutfile<<"Divers: "<<diversind<<endl;
        if(diversind==4){ //AN GIA 3H FORA SYNEXOMENA DEN VRIKES KALI LYSI PANE PISW STIN TELEYTAIA KALI
            diversind=0;
        
            for(int recover=0;recover<solind;recover++){
                solInvestment[recover]=recoverInvestment[recover];
                solCost[recover]=recoverCost[recover];
                solProfit[recover]=recoverProfit[recover];
                solJobs[recover]=recoverJobs[recover];
            }
            detailedOutfile<<endl<<"Recover to ";
            for(i=0;i<solind;i++) detailedOutfile<<recoverInvestment[i]<<" ";
            detailedOutfile<<endl;
        }
    } //END TABU LOOP

    detailedOutfile<<endl<<"-----------------------------------------------------------"<<endl; //TYPWSE TA TELEYTAIA APOTELESMATA
        for(i=0;i<solind;i++){
            simpleOutfile<<bestInvestment[i]<<" ";
        }
        simpleOutfile<<endl<<"cost= "<<bestCost<<" zBest= "<<zBest<<" jobs= "<<jobBest<<endl;
        simpleOutfile<<"Tabu= ";
        for(tabuind=0;tabuind<6;tabuind++)
            simpleOutfile<<tabuList[tabuind]<<"  ";

        simpleOutfile<<endl;
        for(i=0;i<solind;i++){
            detailedOutfile<<bestInvestment[i]<<" ";
        }
        detailedOutfile<<endl<<"cost= "<<bestCost<<" zBest= "<<zBest<<" jobs= "<<jobBest<<endl;
        detailedOutfile<<"Tabu= ";
        for(tabuind=0;tabuind<6;tabuind++)
            detailedOutfile<<tabuList[tabuind]<<"  ";

        detailedOutfile<<endl;

    }

    return 0;
}