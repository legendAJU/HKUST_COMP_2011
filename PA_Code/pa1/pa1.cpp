// === Region: Project Declaration ===
//
//  COMP2011 Fall 2025
//  PA1: Hospital Simulation
//
//  Your name:
//  Your ITSC email:           @connect.ust.hk
//
//  Note: Generative AI is NOT allowed in completing your lab exercises or programming assignments
//  Reference: https://course.cse.ust.hk/comp2011/web/code.html
//
//  Declaration:
//  I declare that I am not involved in plagiarism
//  I understand that both parties (i.e., students providing the codes and students copying the codes) will receive 0 marks.
//
//  Project TA: Peter CHUNG (cspeter@cse.ust.hk)
//
//  For code-level questions, please send a direct email to the above TA.
//  Asking questions with code blocks in a public discussion forum (e.g., Piazza) may cause plagiarism issues
//  Usually, you will get the quickest response via a direct email.
//
// =====================================

#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

// There are 5 possible patient status:
// STATUS_WAITING - The patient is waiting for consultation
// STATUS_CONSULTING - The patient is receiving consultation
// STATUS_QUIT - The patient quits because s/he exceeds his/her maximum waiting time
// STATUS_CURED - The patient cures after the consultation
// STATUS_DEAD - The patient dies because his/her sickness level reaches the fatal sickness value
enum PatientStatus
{
    STATUS_WAITING = 0,
    STATUS_CONSULTING = 1,
    STATUS_QUIT = 2,
    STATUS_CURED = 3,
    STATUS_DEAD = 4
};

const int MAX_DOCTORS = 10;
const int MAX_PATIENTS = 10;
const int FATAL_SICKNESS_VALUE = 44;

const char SIMULATE_END[] = "!!";
const char SIMULATE_FIRST_COME_FIRST_SERVE[] = "First-Come-First-Serve";
const char SIMULATE_HIGHEST_SICKNESS_FIRST[] = "Highest-Sickness-First";
const char SIMULATE_SHORTEST_TREATMENT_TIME_FIRST[] = "Shortest-Treatment-Time-First";

// Helper function: Read and initialize the input
void readAndInitInput(int &numDoctors, int &numPatients,
                      int sickness[MAX_PATIENTS],
                      int treatmentTime[MAX_PATIENTS],
                      int maxWaitTime[MAX_PATIENTS],
                      PatientStatus patientStatus[MAX_PATIENTS])
{
    char textPrompt[100]; // skip the first C-string
    int i;
    // 1st line: Doctors [numDoctors]
    cin >> textPrompt >> numDoctors;
    // 2nd line: Patients [numPatients]
    cin >> textPrompt >> numPatients;
    // 3rd line: Sickness [Array of sickness values]
    cin >> textPrompt;
    for (i = 0; i < numPatients; i++)
    {
        cin >> sickness[i];
    }
    // 4th line: TreatmentTime [Array of treatment time]
    cin >> textPrompt;
    for (i = 0; i < numPatients; i++)
    {
        cin >> treatmentTime[i];
    }
    // 5th line: MaxWaitTime [Array of MaxWaitTime]
    cin >> textPrompt;
    for (i = 0; i < numPatients; i++)
    {
        cin >> maxWaitTime[i];
    }

    // initialize arrays
    for (i = 0; i < numPatients; i++)
    {
        patientStatus[i] = STATUS_WAITING;
    }
}

// Helper function: compare 2 c-string
bool equalCString(const char s1[], const char s2[])
{
    return strcmp(s1, s2) == 0;
}

// Helper function: print doctor and patient
void printDoctorAndPatient(int doctorIndex, int patientIndex)
{
    cout << "D" << doctorIndex << "(P" << patientIndex << ") ";
}
// Helper function: print doctor without patient
void printDoctorWithoutPatient(int doctorIndex)
{
    cout << "D" << doctorIndex << "(  )" << " ";
}
// Helper function: print current time
void printCurrentTime(int time)
{
    cout << setw(3) << time << ": ";
}

void swap(int& x, int& y){
    int temp = x;
    x = y;
    y = temp;
}

// TODO: simulate first-come-first-serve method
/**
 * function: simulateFirstComeFirstServe
 * This function simulates the consultations using the first-come-first serve approach
 * Note: most of the array are passed as constant to avoid changing array values in the main function
 *
 * @param numDoctors: number of doctors for this simulation
 * @param numPatients: number of patients for this simulation
 * @param sickness: an array of patient's sickness level
 * @param treatmentTime: an array of patient's treatment time
 * @param maxWaitTime: an array of patient's maximum waiting time
 * @param patientStatus: an array of patient's status. For details, please refer to the above enum definition
 */
void simulateFirstComeFirstServe(int numDoctors, int numPatients,
                                 const int sickness[],
                                 const int treatmentTime[],
                                 const int maxWaitTime[],
                                 const PatientStatus patientStatus[])
{
    cout << "=== Start: First-Come-First-Serve ===" << endl;

    // TODO: Write your code here
    // initial doctor status
    int doctorStatus[numDoctors]; // Track doctor's status, -1 = free, others = patientId
    for (int i = 0; i < numDoctors; i++)
    {
        doctorStatus[i] = -1;
    }
    //copy properties of patient
    int copyOfSickness[numPatients],copyOfTreatmentTime[numPatients],copyOfMaxWaitTime[numPatients];
    PatientStatus copyOfPatientStatus[numPatients];
    for (int i = 0; i < numPatients; i++)
    {
        copyOfSickness[i] = sickness[i];
        copyOfTreatmentTime[i] = treatmentTime[i];
        copyOfMaxWaitTime[i] = maxWaitTime[i];
        copyOfPatientStatus[i] = patientStatus[i]; 
    }
    int time=0;
    int numCure = 0, numQuit = 0, numDead = 0, numDoctorIdleTime = 0;

    //Start simulation
    while(true)
    {
        printCurrentTime(time);
        time++;
        //phase 1: Assign Patiens to idle doctors
        for (int i = 0; i < numDoctors; i++)
        {   
            if(doctorStatus[i] == -1) //doctor free
            {
                for (int j = 0; j < numPatients; j++)// find suitbale patient
                {
                    PatientStatus currStatus = copyOfPatientStatus[j];
                    if(currStatus == STATUS_WAITING){
                        doctorStatus[i] = j;
                        copyOfPatientStatus[j] = STATUS_CONSULTING;
                        break;
                    }
                }
            }
        }
        //phase 2 & 3: Update sickness level && waiting time
        for (int i = 0; i < numPatients; i++)
        {
            PatientStatus currStatus = copyOfPatientStatus[i];
            if(currStatus == STATUS_WAITING){
                copyOfSickness[i]++;
                if(copyOfSickness[i] == FATAL_SICKNESS_VALUE){
                    copyOfPatientStatus[i] = STATUS_DEAD;
                    numDead++;
                }
                else{
                    copyOfMaxWaitTime[i]--;
                    if(copyOfMaxWaitTime[i] == -1){
                        copyOfPatientStatus[i] = STATUS_QUIT;
                        numQuit++;
                    }
                }
            }
        }
        //phase 4: consult with doc, update patients information and display
        for (int i = 0; i < numDoctors; i++)
        {   
            if(doctorStatus[i] != -1){
                printDoctorAndPatient(i,doctorStatus[i]);
                copyOfTreatmentTime[doctorStatus[i]]--;
                if(copyOfTreatmentTime[doctorStatus[i]] == 0){
                    copyOfPatientStatus[doctorStatus[i]] = STATUS_CURED;
                    numCure++;
                    doctorStatus[i] = -1;
                }
            }
            else{
                numDoctorIdleTime++;
                printDoctorWithoutPatient(i);
            }
            
        }
        cout<<endl;
        if(numCure+numDead+numQuit == numPatients){
            cout<<"Total cure: " << numCure<<endl;
            cout<<"Total quit: "<< numQuit<<endl;
            cout<<"Total dead: "<< numDead<<endl;
            cout<<"Total doctor idle time: "<< numDoctorIdleTime<<endl;
            break;
        }
    }

    cout << "=== End: First-Come-First-Serve ===" << endl;
}

// TODO: simulate highest sickness patient first
// Note: if there are more than patients with the same highest sickness,
// pick the earliest arrival patient
/**
 * function: simulateHighestSicknessFirst
 * This function simulates the consultations using the highest-sickness-first approach
 * Note: most of the array are passed as constant to avoid changing array values in the main function
 *
 * @param numDoctors: number of doctors for this simulation
 * @param numPatients: number of patients for this simulation
 * @param sickness: an array of patient's sickness level
 * @param treatmentTime: an array of patient's treatment time
 * @param maxWaitTime: an array of patient's maximum waiting time
 * @param patientStatus: an array of patient's status. For details, please refer to the above enum definition
 */
void simulateHighestSicknessFirst(int numDoctors, int numPatients,
                                  const int sickness[],
                                  const int treatmentTime[],
                                  const int maxWaitTime[],
                                  const PatientStatus patientStatus[])
{
    cout << "=== Start: Highest-Sickness-First ===" << endl;

     int doctorStatus[numDoctors]; // Track doctor's status, -1 = free, others = patientId
    for (int i = 0; i < numDoctors; i++)
    {
        doctorStatus[i] = -1;
    }
    int copyOfSickness[numPatients],copyOfTreatmentTime[numPatients],copyOfMaxWaitTime[numPatients],indexOfPatients[numPatients];
    PatientStatus copyOfPatientStatus[numPatients];
    //copy array
    for (int i = 0; i < numPatients; i++)
    {
        copyOfSickness[i] = sickness[i];
        copyOfTreatmentTime[i] = treatmentTime[i];
        copyOfMaxWaitTime[i] = maxWaitTime[i];
        indexOfPatients[i] = i;
        copyOfPatientStatus[i] = patientStatus[i];
    }
    int time = 0;
    int numCure = 0, numQuit = 0, numDead = 0, numDoctorIdleTime = 0;

    // sort by sickness
    for (int i = 0; i < numPatients; i++)
    {
        for (int j = 0; j < numPatients - i - 1; j++)
        {
            if(copyOfSickness[j] < copyOfSickness[j + 1]){
                swap(copyOfTreatmentTime[j],copyOfTreatmentTime[j + 1]);
                swap(copyOfMaxWaitTime[j],copyOfMaxWaitTime[j + 1]);
                swap(copyOfSickness[j],copyOfSickness[j + 1]);
                swap(indexOfPatients[j],indexOfPatients[j + 1]);
            }
        }
    }


    //start simulation
    while(true)
    {
        printCurrentTime(time);
        time++;
        //phase 1: Assign Patiens to idle doctors
        for (int i = 0; i < numDoctors; i++)
        {   
            if(doctorStatus[i] == -1) //doctor free
            {
                for (int j = 0; j < numPatients; j++)// find suitbale patient
                {
                    PatientStatus currStatus = copyOfPatientStatus[j];
                    if(currStatus == STATUS_WAITING){
                        doctorStatus[i] = j;
                        copyOfPatientStatus[j] = STATUS_CONSULTING;
                        break;
                    }
                }
            }
        }
        //phase 2 & 3: Update sickness level && waiting time
        for (int i = 0; i < numPatients; i++)
        {
            PatientStatus currStatus = copyOfPatientStatus[i];
            if(currStatus == STATUS_WAITING){
                copyOfSickness[i]++;
                if(copyOfSickness[i] == FATAL_SICKNESS_VALUE){
                    copyOfPatientStatus[i] = STATUS_DEAD;
                    numDead++;
                }
                else{
                    copyOfMaxWaitTime[i]--;
                    if(copyOfMaxWaitTime[i] == -1){
                        copyOfPatientStatus[i] = STATUS_QUIT;
                        numQuit++;
                    }
                }
            }
        }
        //phase 4: consult with doc, update patients information and display
        for (int i = 0; i < numDoctors; i++)
        {   
            if(doctorStatus[i] != -1){
                printDoctorAndPatient(i,indexOfPatients[doctorStatus[i]]);
                copyOfTreatmentTime[doctorStatus[i]]--;
                if(copyOfTreatmentTime[doctorStatus[i]] == 0){
                    copyOfPatientStatus[doctorStatus[i]] = STATUS_CURED;
                    numCure++;
                    doctorStatus[i] = -1;
                }
            }
            else{
                numDoctorIdleTime++;
                printDoctorWithoutPatient(i);
            }
            
        }
        cout<<endl;
        if(numCure+numDead+numQuit == numPatients){
            cout<<"Total cure: " << numCure<<endl;
            cout<<"Total quit: "<< numQuit<<endl;
            cout<<"Total dead: "<< numDead<<endl;
            cout<<"Total doctor idle time: "<< numDoctorIdleTime<<endl;
            break;
        }
    }
    
    cout << "=== End: Highest-Sickness-First ===" << endl;
}

// TODO: simulate shortest treatment time first
// Note: if there are more than patients with the same smallest treatment time,
// pick the earliest arrival patient
/**
 * function: simulateShortestTreatmentTimeFirst
 * This function simulates the consultations using the shortest-treatment-time approach
 * Note: most of the array are passed as constant to avoid changing array values in the main function
 *
 * @param numDoctors: number of doctors for this simulation
 * @param numPatients: number of patients for this simulation
 * @param sickness: an array of patient's sickness level
 * @param treatmentTime: an array of patient's treatment time
 * @param maxWaitTime: an array of patient's maximum waiting time
 * @param patientStatus: an array of patient's status. For details, please refer to the above enum definition
 */
void simulateShortestTreatmentTimeFirst(int numDoctors, int numPatients,
                                        const int sickness[],
                                        const int treatmentTime[],
                                        const int maxWaitTime[],
                                        const PatientStatus patientStatus[])
{
    cout << "=== Start: Shortest-Treatment-Time-First ===" << endl;

    int doctorStatus[numDoctors]; // Track doctor's status, -1 = free, others = patientId
    for (int i = 0; i < numDoctors; i++)
    {
        doctorStatus[i] = -1;
    }
    int copyOfSickness[numPatients],copyOfTreatmentTime[numPatients],copyOfMaxWaitTime[numPatients],indexOfPatients[numPatients];
    PatientStatus copyOfPatientStatus[numPatients];
    //copy array
    for (int i = 0; i < numPatients; i++)
    {
        copyOfSickness[i] = sickness[i];
        copyOfTreatmentTime[i] = treatmentTime[i];
        copyOfMaxWaitTime[i] = maxWaitTime[i];
        indexOfPatients[i] = i;
        copyOfPatientStatus[i] = patientStatus[i];
    }
    int time = 0;
    int numCure = 0, numQuit = 0, numDead = 0, numDoctorIdleTime = 0;
    //sort by treatment time, record the index.
    for (int i = 0; i < numPatients; i++)
    {
        for (int j = 0; j < numPatients - i - 1; j++)
        {
            if(copyOfTreatmentTime[j] > copyOfTreatmentTime[j + 1]){
                swap(copyOfTreatmentTime[j],copyOfTreatmentTime[j + 1]);
                swap(copyOfMaxWaitTime[j],copyOfMaxWaitTime[j + 1]);
                swap(copyOfSickness[j],copyOfSickness[j + 1]);
                swap(indexOfPatients[j],indexOfPatients[j + 1]);
            }
        }
    }

    //start simulation
    while(true)
    {
        printCurrentTime(time);
        time++;
        //phase 1: Assign Patiens to idle doctors
        for (int i = 0; i < numDoctors; i++)
        {   
            if(doctorStatus[i] == -1) //doctor free
            {
                for (int j = 0; j < numPatients; j++)// find suitbale patient
                {
                    PatientStatus currStatus = copyOfPatientStatus[j];
                    if(currStatus == STATUS_WAITING){
                        doctorStatus[i] = j;
                        copyOfPatientStatus[j] = STATUS_CONSULTING;
                        break;
                    }
                }
            }
        }
        //phase 2 & 3: Update sickness level && waiting time
        for (int i = 0; i < numPatients; i++)
        {
            PatientStatus currStatus = copyOfPatientStatus[i];
            if(currStatus == STATUS_WAITING){
                copyOfSickness[i]++;
                if(copyOfSickness[i] == FATAL_SICKNESS_VALUE){
                    copyOfPatientStatus[i] = STATUS_DEAD;
                    numDead++;
                }
                else{
                    copyOfMaxWaitTime[i]--;
                    if(copyOfMaxWaitTime[i] == -1){
                        copyOfPatientStatus[i] = STATUS_QUIT;
                        numQuit++;
                    }
                }
            }
        }
        //phase 4: consult with doc, update patients information and display
        for (int i = 0; i < numDoctors; i++)
        {   
            if(doctorStatus[i] != -1){
                printDoctorAndPatient(i,indexOfPatients[doctorStatus[i]]);
                copyOfTreatmentTime[doctorStatus[i]]--;
                if(copyOfTreatmentTime[doctorStatus[i]] == 0){
                    copyOfPatientStatus[doctorStatus[i]] = STATUS_CURED;
                    numCure++;
                    doctorStatus[i] = -1;
                }
            }
            else{
                numDoctorIdleTime++;
                printDoctorWithoutPatient(i);
            }
            
        }
        cout<<endl;
        if(numCure+numDead+numQuit == numPatients){
            cout<<"Total cure: " << numCure<<endl;
            cout<<"Total quit: "<< numQuit<<endl;
            cout<<"Total dead: "<< numDead<<endl;
            cout<<"Total doctor idle time: "<< numDoctorIdleTime<<endl;
            break;
        }
    }
    


    cout << "=== End: Shortest-Treatment-Time-First ===" << endl;
}

int main()
{
    int numDoctors, numPatients;
    int sickness[MAX_PATIENTS];
    int treatmentTime[MAX_PATIENTS];
    int maxWaitTime[MAX_PATIENTS];
    PatientStatus patientStatus[MAX_PATIENTS];

    // Step 1: Read and initalize input values
    readAndInitInput(numDoctors, numPatients, sickness, treatmentTime, maxWaitTime, patientStatus);

    // Step 2: A main loop to handle different simulations
    char textPrompt[100];     // skip the first C-string
    char simulationName[100]; // store the name of the simulation
    // Each line has the format: Simulate [simulationName]
    while (true)
    {
        cin >> textPrompt >> simulationName;
        if (equalCString(simulationName, SIMULATE_END))
            break;

        if (equalCString(simulationName, SIMULATE_FIRST_COME_FIRST_SERVE))
        {
            simulateFirstComeFirstServe(numDoctors, numPatients, sickness, treatmentTime, maxWaitTime, patientStatus);
        }
        else if (equalCString(simulationName, SIMULATE_HIGHEST_SICKNESS_FIRST))
        {
            simulateHighestSicknessFirst(numDoctors, numPatients, sickness, treatmentTime, maxWaitTime, patientStatus);
        }
        else if (equalCString(simulationName, SIMULATE_SHORTEST_TREATMENT_TIME_FIRST))
        {
            simulateShortestTreatmentTimeFirst(numDoctors, numPatients, sickness, treatmentTime, maxWaitTime, patientStatus);
        }
    }

    return 0;
}