/*** Allard Group jun.allard@uci.edu                    ***/

void runGillespie();
int findPathIndex();

/*******************************************************************************/
//  GLOBAL VARIABLES
/*******************************************************************************/

double remainderFactorial;
double remainderVector[ISITEMAX];
double positionInRemainder[ISITEMAX];



/*******************************************************************************/
void runGillespie()
{
    
    /****************************** Create State Matrix from File ***********************/

    sizeOfStateMatrix = (int) pow(2,iSiteTotal);
    
    
    char line[200];
    i=0;
    j=0;
    
    ratesFile = fopen(matrixName,"r");
    
    while (fgets(line, sizeof(line), ratesFile))
    {
        stateMatrix[i][j]=atof(line);
        j++;
        if ((j%iSiteTotal) == 0)
        {
            i++;
            j=0;
        }
            
    }
    
    fclose(ratesFile);
    
    //debugging
    if(0)
    {
        for (i=0;i<sizeOfStateMatrix;i++)
        {
            for (j=0;j<iSiteTotal;j++)
            {
                printf("%lf ", stateMatrix[i][j]);
            
            }
        
            printf("\n");
        }
    }

    /****************************** Initialize Variables ***********************/
    for(iy=0;iy<iSiteTotal;iy++)
    {
        transitionTime[iy] = 0;
    }
    
    /******************************* Gillespie ******************************************/
    
    
    timeSum=0;
    it=0;
    
    while (it < iterations && it < ITMAX)
    {
    
    
        timeTotal=0;
        
        currentState=0;
        stepCount = 0;
        for(i=0;i<iSiteTotal;i++)
        {
            path[i]=0;
        }
        
        while (currentState < pow(2,iSiteTotal)-1) //while loop vs for loop?
        {
            
            
            //initialize random time array and time step
            for (iy=0;iy<iSiteTotal;iy++)
            {
                randTime[iy]=0;
            }
            
            timeStep = INF;
            
            //Gillespie step
            
            for (iy=0;iy<iSiteTotal;iy++)
            {
                if (stateMatrix[currentState][iy]!=0)
                {
                    randTime[iy] = - log(TWISTER)/stateMatrix[currentState][iy]; //exponentially distributed random variable based on transition rate
                }
                else
                {
                    randTime[iy] = 0; //use 0 instead of infinity - then just remove these cases later
                }
            }
            
            //pick smallest of random times
            for (iy=0;iy<iSiteTotal;iy++)
            {
                if (randTime[iy]!= 0)  // 0 time is not an option
                {
                    if (randTime[iy]<timeStep)
                    {
                        timeStep = randTime[iy];
                        newState = iy;
                    }
                }
            }
            
            if (0)
            printf("This is the path chosen: %d\n", newState);
            
            // create path number
            //use this update for "forwards" transitionMatrix (i.e. forwards binary, backwards phosphorylation)
            path[stepCount] = (iSiteTotal-newState);
            //path += (iSiteTotal-newState)*pow(10,(iSiteTotal-stepCount-1));

            
            // use this update for "backwards" transitionMatrix (i.e. backwards binary)
            //path[stepCount] = (newState+1);
            //path += (newState+1)*pow(10,(iSiteTotal-stepCount-1));

            // record time to transition
            transitionTime[stepCount] += timeStep;
            
            if(0)//debugging
                printf("Transition: %d, Time: %f\n",stepCount,timeStep);
            
            //update time and state
            timeTotal += timeStep;
            stepCount++;
            
            // use this update for "forwards" transitionMatrix (i.e. forwards binary, backwards phosphorylation)
            currentState += pow(2,newState);
            
            // use this update for "backwards" transitionMatrix
            //currentState += pow(2,iSiteTotal-newState-1);
            
            if (0)
            printf("Current State is: %d \n", currentState);
            
            
        }
        
        // record which path is used and how long it took
        pathIndex = findPathIndex();
        pathArray[pathIndex][0]++;
        pathArray[pathIndex][1] += timeTotal;
        
        //debugging
        if(0)
        {
            printf("Path index: %d\n",pathIndex);
            fflush(stdout);
        }
        
        
        //for MFPT
        timeSum += timeTotal;
        
        
        if (TIME)
        {
            timeArray[it] = timeTotal;
        }
        
        it++;
    
    }
    
    outputGillespie();
    
    
}


/********** Find index of path ***********/
/** code to accept a permutation of the values 1...iSiteTotal and return the index of that permutation in the ordered set of all permutations 1...iSiteTotal **/
int findPathIndex()
{
    
    //debugging
    if(0)
    {
        printf("Path:\n");
        fflush(stdout);
        for(i=0;i<iSiteTotal;i++)
        {
            printf("%f ",path[i]);
            fflush(stdout);
        }
    }
    
    // initialize
    int nullcounter;
    int pathIndex = 0; // start at 0 since C indexing begins at 0, start at 1 in language beginning with 1
    
    for (i=1;i<=iSiteTotal;i++)
    {
        remainderVector[i-1] = i;
        positionInRemainder[i-1] = 0;
    }
    
    // find index
    for(i=1;i<=iSiteTotal;i++)
    {
        j=1;
        nullcounter = 0;
        while(remainderVector[j-1]!=path[i-1] && j<=iSiteTotal)
        {
            if(remainderVector[j-1]==-1)
            {
                nullcounter++;
            }
            j++;
        }
        positionInRemainder[i-1] = j-nullcounter;
        remainderVector[j-1] = -1;
        
        remainderFactorial = 1;
        if((iSiteTotal-(i-1)-1) > 0)
        {
        for(k=1;k<=(iSiteTotal-(i-1)-1);k++)
        {
            remainderFactorial *= k;
        }
        }
        else
        {
            if((iSiteTotal-(i-1)-1)==0)
                remainderFactorial = 1;
        }
        
        pathIndex += (positionInRemainder[i-1]-1)*remainderFactorial;
        
        
    }
    
    //debugging
    if(0)
    {
        printf("Path index: %d\n",pathIndex);
        fflush(stdout);
    }
    
    return pathIndex;
    
}







