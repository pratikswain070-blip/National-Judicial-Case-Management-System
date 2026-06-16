#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// This program keeps the data structures simple and visible:
// 1. Array for storing all cases
// 2. Queue for filing order
// 3. Max heap for urgent cases
// 4. Graph arrays for citations and appeals

const int MAX_NODES = 1000;
const int MAX_LINKS = 50;

// ---------- Case Structure ----------
struct Case {
    int id;
    string title;
    string type;        // Criminal, Civil, Constitutional, Commercial
    int priority;       // 1-10, where higher means more urgent
    string status;      // Registered, Scheduled, Under Hearing, Resolved
    string hearingDate;
};

// ---------- Global Data ----------
Case allCases[MAX_NODES];
int totalCases = 0;

Case filingQueue[MAX_NODES];
int qFront = 0;
int qRear = 0;

struct UrgentCase {
    int priority;
    int id;
};

UrgentCase urgentHeap[MAX_NODES];
int heapSize = 0;

int citationGraph[MAX_NODES][MAX_LINKS];
int citationCount[MAX_NODES] = {0};

int appealGraph[MAX_NODES][MAX_LINKS];
int appealCount[MAX_NODES] = {0};

void saveToSampleData(); // Forward declaration for auto-saving

// ---------- Small Helper Functions ----------
char toSmallLetter(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch + 32;
    }
    return ch;
}

string makeLowercase(string text) {
    string result = "";

    for (int i = 0; i < (int)text.length(); i++) {
        result += toSmallLetter(text[i]);
    }

    return result;
}

void swapCases(Case &first, Case &second) {
    Case temp = first;
    first = second;
    second = temp;
}

void swapUrgentCases(UrgentCase &first, UrgentCase &second) {
    UrgentCase temp = first;
    first = second;
    second = temp;
}

void printCaseShort(Case c) {
    cout << "ID: " << c.id
         << " | " << c.title
         << " | Type: " << c.type
         << " | Priority: " << c.priority
         << " | Status: " << c.status << endl;
}

void printCaseDetails(Case c) {
    cout << "ID       : " << c.id << endl;
    cout << "Title    : " << c.title << endl;
    cout << "Type     : " << c.type << endl;
    cout << "Priority : " << c.priority << endl;
    cout << "Status   : " << c.status << endl;
    cout << "Hearing  : " << c.hearingDate << endl;
}

// ---------- Queue Functions ----------
void enqueue(Case c) {
    if (qRear < MAX_NODES) {
        filingQueue[qRear] = c;
        qRear++;
    }
}

Case dequeue() {
    Case firstCase = filingQueue[qFront];
    qFront++;
    return firstCase;
}

int queueSize() {
    return qRear - qFront;
}

// ---------- Max Heap Functions ----------
void heapInsert(int priority, int id) {
    urgentHeap[heapSize].priority = priority;
    urgentHeap[heapSize].id = id;

    int child = heapSize;
    heapSize++;

    while (child > 0) {
        int parent = (child - 1) / 2;

        if (urgentHeap[parent].priority >= urgentHeap[child].priority) {
            break;
        }

        swapUrgentCases(urgentHeap[parent], urgentHeap[child]);
        child = parent;
    }
}

UrgentCase heapExtractMax() {
    UrgentCase highestPriorityCase = urgentHeap[0];

    heapSize--;
    urgentHeap[0] = urgentHeap[heapSize];

    int parent = 0;

    while (true) {
        int leftChild = 2 * parent + 1;
        int rightChild = 2 * parent + 2;
        int biggest = parent;

        if (leftChild < heapSize &&
            urgentHeap[leftChild].priority > urgentHeap[biggest].priority) {
            biggest = leftChild;
        }

        if (rightChild < heapSize &&
            urgentHeap[rightChild].priority > urgentHeap[biggest].priority) {
            biggest = rightChild;
        }

        if (biggest == parent) {
            break;
        }

        swapUrgentCases(urgentHeap[parent], urgentHeap[biggest]);
        parent = biggest;
    }

    return highestPriorityCase;
}

// ---------- Graph Functions ----------
void addCitationEdge(int from, int to) {
    if (from >= 0 && from < MAX_NODES && citationCount[from] < MAX_LINKS) {
        citationGraph[from][citationCount[from]] = to;
        citationCount[from]++;
    }
}

void addAppealEdge(int lower, int higher) {
    if (lower >= 0 && lower < MAX_NODES && appealCount[lower] < MAX_LINKS) {
        appealGraph[lower][appealCount[lower]] = higher;
        appealCount[lower]++;
    }
}

int totalCitationCases() {
    int count = 0;

    for (int i = 0; i < MAX_NODES; i++) {
        if (citationCount[i] > 0) {
            count++;
        }
    }

    return count;
}

int totalAppealCases() {
    int count = 0;

    for (int i = 0; i < MAX_NODES; i++) {
        if (appealCount[i] > 0) {
            count++;
        }
    }

    return count;
}

// ---------- Case Helpers ----------
int findCaseIndex(int id) {
    for (int i = 0; i < totalCases; i++) {
        if (allCases[i].id == id) {
            return i;
        }
    }

    return -1;
}

void addCaseToSystem(Case c) {
    enqueue(c);

    if (totalCases < MAX_NODES) {
        allCases[totalCases] = c;
        totalCases++;
    }

    if (c.priority >= 7) {
        heapInsert(c.priority, c.id);
    }
}

void sortAllCasesById() {
    for (int i = 0; i < totalCases - 1; i++) {
        for (int j = 0; j < totalCases - i - 1; j++) {
            if (allCases[j].id > allCases[j + 1].id) {
                swapCases(allCases[j], allCases[j + 1]);
            }
        }
    }
}

void copyCases(Case copiedCases[]) {
    for (int i = 0; i < totalCases; i++) {
        copiedCases[i] = allCases[i];
    }
}

void sortByPriorityHighToLow(Case cases[]) {
    for (int i = 0; i < totalCases - 1; i++) {
        for (int j = 0; j < totalCases - i - 1; j++) {
            if (cases[j].priority < cases[j + 1].priority) {
                swapCases(cases[j], cases[j + 1]);
            }
        }
    }
}

// ========== 1. CASE REGISTRATION (Queue) ==========
void registerCase() {
    Case c;

    cout << "\n--- Register New Case ---\n";
    cout << "Enter Case ID: ";
    cin >> c.id;

    if (findCaseIndex(c.id) != -1) {
        cout << "Error: Case ID already exists!\n";
        return;
    }

    cin.ignore();
    cout << "Enter Title: ";
    getline(cin, c.title);

    cout << "Enter Type (Criminal/Civil/Constitutional/Commercial): ";
    getline(cin, c.type);

    cout << "Enter Priority (1-10): ";
    cin >> c.priority;

    c.status = "Registered";
    c.hearingDate = "Not Scheduled";

    addCaseToSystem(c);

    saveToSampleData();

    cout << "Case " << c.id << " registered successfully!\n";
}

// ========== 2. PROCESS FILING QUEUE (Queue - FIFO) ==========
void processQueue() {
    if (queueSize() == 0) {
        cout << "\nNo cases in filing queue.\n";
        return;
    }

    Case c = dequeue();

    cout << "\n--- Processing Case (FIFO Order) ---\n";
    printCaseShort(c);
}

// ========== 3. URGENT MATTER HANDLING (Priority Queue) ==========
void handleUrgent() {
    if (heapSize == 0) {
        cout << "\nNo urgent cases pending.\n";
        return;
    }

    UrgentCase top = heapExtractMax();
    int index = findCaseIndex(top.id);

    if (index == -1) {
        cout << "Case ID: " << top.id
             << " | Priority: " << top.priority << endl;
        return;
    }

    cout << "\n--- Highest Priority Case ---\n";
    cout << "ID: " << allCases[index].id
         << " | Title: " << allCases[index].title
         << " | Priority: " << top.priority
         << " | Status: " << allCases[index].status << endl;
}

// ========== 4. CASE RETRIEVAL (Binary Search) ==========
void searchCase() {
    if (totalCases == 0) {
        cout << "\nNo cases in system.\n";
        return;
    }

    sortAllCasesById();

    int target;
    cout << "\nEnter Case ID to search: ";
    cin >> target;

    int low = 0;
    int high = totalCases - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (allCases[mid].id == target) {
            cout << "\n--- Case Found ---\n";
            printCaseDetails(allCases[mid]);
            return;
        }

        if (allCases[mid].id < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    cout << "Case not found.\n";
}

// ========== 5. ADD LEGAL CITATION (Graph) ==========
void addCitation() {
    int from;
    int to;

    cout << "\nEnter Case ID: ";
    cin >> from;

    cout << "Enter Cited Case ID: ";
    cin >> to;

    addCitationEdge(from, to);

    saveToSampleData();

    cout << "Citation Added: " << from << " cites " << to << endl;
}

// ========== 6. SHOW PRECEDENT GRAPH (Graph) ==========
void showPrecedents() {
    bool found = false;

    cout << "\n--- Legal Precedent Graph ---\n";

    for (int i = 0; i < MAX_NODES; i++) {
        if (citationCount[i] > 0) {
            found = true;

            cout << "Case " << i << " cites -> ";

            for (int j = 0; j < citationCount[i]; j++) {
                cout << citationGraph[i][j] << " ";
            }

            cout << endl;
        }
    }

    if (!found) {
        cout << "No citations recorded.\n";
    }
}

// ========== 7. ADD APPEAL LINK (Graph) ==========
void addAppeal() {
    int lower;
    int higher;

    cout << "\nEnter Lower Court Case ID: ";
    cin >> lower;

    cout << "\nEnter Higher Court Case ID: ";
    cin >> higher;

    addAppealEdge(lower, higher);

    saveToSampleData();

    cout << "Appeal Linked: " << lower << " -> " << higher << endl;
}

// ========== 8. APPEAL TRACKING (DFS) ==========
void dfs(int node, bool visited[]) {
    visited[node] = true;

    cout << node << " -> ";

    for (int i = 0; i < appealCount[node]; i++) {
        int next = appealGraph[node][i];

        if (!visited[next]) {
            dfs(next, visited);
        }
    }
}

void trackAppeal() {
    int start;

    cout << "\nEnter Starting Case ID: ";
    cin >> start;

    bool visited[MAX_NODES];

    for (int i = 0; i < MAX_NODES; i++) {
        visited[i] = false;
    }

    cout << "\nAppeal Journey: ";
    dfs(start, visited);
    cout << "END\n";
}

// ========== 9. VIEW ALL CASES (Sorted by Priority) ==========
void viewAllCases() {
    if (totalCases == 0) {
        cout << "\nNo cases in system.\n";
        return;
    }

    Case sortedCases[MAX_NODES];
    copyCases(sortedCases);
    sortByPriorityHighToLow(sortedCases);

    cout << "\n--- All Cases (Sorted by Priority: High to Low) ---\n";
    cout << "----------------------------------------------------------------------\n";

    for (int i = 0; i < totalCases; i++) {
        printCaseShort(sortedCases[i]);
    }

    cout << "----------------------------------------------------------------------\n";
    cout << "Total Cases: " << totalCases << endl;
}

// ========== 10. FILTER CASES BY TYPE ==========
void filterByType() {
    if (totalCases == 0) {
        cout << "\nNo cases in system.\n";
        return;
    }

    cin.ignore();

    string target;
    cout << "\nEnter Type to filter (Criminal/Civil/Constitutional/Commercial): ";
    getline(cin, target);

    string targetLower = makeLowercase(target);
    bool found = false;

    cout << "\n--- Cases of Type: " << target << " ---\n";

    for (int i = 0; i < totalCases; i++) {
        string typeLower = makeLowercase(allCases[i].type);

        if (typeLower.find(targetLower) != string::npos) {
            cout << "ID: " << allCases[i].id
                 << " | " << allCases[i].title
                 << " | Priority: " << allCases[i].priority
                 << " | Status: " << allCases[i].status << endl;

            found = true;
        }
    }

    if (!found) {
        cout << "No cases found for type \"" << target << "\".\n";
    }
}

// ========== 11. UPDATE CASE STATUS ==========
void updateStatus() {
    int id;

    cout << "\nEnter Case ID: ";
    cin >> id;

    int index = findCaseIndex(id);

    if (index == -1) {
        cout << "Case not found.\n";
        return;
    }

    cout << "Current Status: " << allCases[index].status << endl;
    cout << "Select New Status:\n";
    cout << "  1. Registered\n";
    cout << "  2. Scheduled\n";
    cout << "  3. Under Hearing\n";
    cout << "  4. Resolved\n";
    cout << "Choice: ";

    int option;
    cin >> option;

    switch (option) {
        case 1:
            allCases[index].status = "Registered";
            break;
        case 2:
            allCases[index].status = "Scheduled";
            break;
        case 3:
            allCases[index].status = "Under Hearing";
            break;
        case 4:
            allCases[index].status = "Resolved";
            break;
        default:
            cout << "Invalid choice.\n";
            return;
    }

    cout << "Status updated to \"" << allCases[index].status << "\".\n";

    saveToSampleData();
}

// ========== 12. SCHEDULE HEARING ==========
void scheduleHearing() {
    int id;

    cout << "\nEnter Case ID: ";
    cin >> id;

    int index = findCaseIndex(id);

    if (index == -1) {
        cout << "Case not found.\n";
        return;
    }

    cin.ignore();

    cout << "Enter Hearing Date (e.g. 2026-07-15): ";
    getline(cin, allCases[index].hearingDate);

    allCases[index].status = "Scheduled";

    cout << "Hearing scheduled for Case " << id
         << " on " << allCases[index].hearingDate << endl;

    saveToSampleData();
}

// ========== 13. DASHBOARD STATISTICS ==========
void showDashboard() {
    int registered = 0;
    int scheduled = 0;
    int hearing = 0;
    int resolved = 0;

    int criminal = 0;
    int civil = 0;
    int constitutional = 0;
    int commercial = 0;

    int urgent = 0;

    for (int i = 0; i < totalCases; i++) {
        Case c = allCases[i];

        if (c.status == "Registered") {
            registered++;
        } else if (c.status == "Scheduled") {
            scheduled++;
        } else if (c.status == "Under Hearing") {
            hearing++;
        } else if (c.status == "Resolved") {
            resolved++;
        }

        string typeLower = makeLowercase(c.type);

        if (typeLower == "criminal") {
            criminal++;
        } else if (typeLower == "civil") {
            civil++;
        } else if (typeLower == "constitutional") {
            constitutional++;
        } else if (typeLower == "commercial") {
            commercial++;
        }

        if (c.priority >= 7) {
            urgent++;
        }
    }

    cout << "\n============= COURT DASHBOARD =============\n";
    cout << " Total Cases        : " << totalCases << endl;
    cout << "-------------------------------------------\n";
    cout << " By Status:\n";
    cout << "   Registered       : " << registered << endl;
    cout << "   Scheduled        : " << scheduled << endl;
    cout << "   Under Hearing    : " << hearing << endl;
    cout << "   Resolved         : " << resolved << endl;
    cout << "-------------------------------------------\n";
    cout << " By Type:\n";
    cout << "   Criminal         : " << criminal << endl;
    cout << "   Civil            : " << civil << endl;
    cout << "   Constitutional   : " << constitutional << endl;
    cout << "   Commercial       : " << commercial << endl;
    cout << "-------------------------------------------\n";
    cout << " Urgent Cases (P>=7): " << urgent << endl;
    cout << " Pending in Queue   : " << queueSize() << endl;
    cout << " Citations Recorded : " << totalCitationCases() << endl;
    cout << " Appeal Links       : " << totalAppealCases() << endl;
    cout << "=============================================\n";
}

// ========== 14. MOST INFLUENTIAL CASE (Most Cited) ==========
void mostInfluential() {
    int citedCount[MAX_NODES];

    for (int i = 0; i < MAX_NODES; i++) {
        citedCount[i] = 0;
    }

    for (int i = 0; i < MAX_NODES; i++) {
        for (int j = 0; j < citationCount[i]; j++) {
            int citedCaseId = citationGraph[i][j];
            citedCount[citedCaseId]++;
        }
    }

    int mostCitedId = -1;
    int highestCount = 0;

    for (int i = 0; i < MAX_NODES; i++) {
        if (citedCount[i] > highestCount) {
            highestCount = citedCount[i];
            mostCitedId = i;
        }
    }

    if (mostCitedId == -1) {
        cout << "\nNo citations recorded.\n";
        return;
    }

    cout << "\n--- Most Influential Judgment ---\n";
    cout << "Case ID: " << mostCitedId
         << " | Cited " << highestCount << " time(s)\n";

    int index = findCaseIndex(mostCitedId);

    if (index != -1) {
        cout << "Title: " << allCases[index].title << endl;
    }
}

// ========== 15. DETECT CIRCULAR CITATIONS ==========
bool dfsCycle(int node, int state[]) {
    state[node] = 1;

    for (int i = 0; i < citationCount[node]; i++) {
        int next = citationGraph[node][i];

        if (state[next] == 1) {
            return true;
        }

        if (state[next] == 0 && dfsCycle(next, state)) {
            return true;
        }
    }

    state[node] = 2;
    return false;
}

void detectCircularCitations() {
    int state[MAX_NODES];

    for (int i = 0; i < MAX_NODES; i++) {
        state[i] = 0;
    }

    bool hasCycle = false;

    for (int i = 0; i < MAX_NODES; i++) {
        if (citationCount[i] > 0 && state[i] == 0) {
            if (dfsCycle(i, state)) {
                hasCycle = true;
                break;
            }
        }
    }

    if (hasCycle) {
        cout << "\n[WARNING] Circular Citation Detected!\n";
    } else {
        cout << "\n[OK] No Circular Citations.\n";
    }
}

// ========== SAVE DATA TO HEADER ==========
void saveToSampleData() {
    ofstream out("sample_data.h");
    if (!out) return;

    out << "#ifndef SAMPLE_DATA_H\n";
    out << "#define SAMPLE_DATA_H\n\n";
    out << "#include <iostream>\n";
    out << "#include <string>\n\n";
    
    // Suppress IDE linter errors partially
    out << "struct Case;\n";
    out << "void addCaseToSystem(Case c);\n";
    out << "void addCitationEdge(int from, int to);\n";
    out << "void addAppealEdge(int lower, int higher);\n";
    out << "int totalCitationCases();\n";
    out << "int totalAppealCases();\n\n";

    out << "// This file gives the program ready-made data for testing.\n";
    out << "void loadSampleData() {\n";
    out << "    Case cases[] = {\n";

    for (int i = 0; i < totalCases; i++) {
        Case c = allCases[i];
        out << "        {" << c.id << ", \"" << c.title << "\", \"" << c.type << "\", "
            << c.priority << ", \"" << c.status << "\", \"" << c.hearingDate << "\"}";
        if (i < totalCases - 1) {
            out << ",\n";
        } else {
            out << "\n";
        }
    }
    
    out << "    };\n\n";
    out << "    int numberOfCases = sizeof(cases) / sizeof(cases[0]);\n\n";
    out << "    // Add every sample case to the main array, queue, and urgent heap.\n";
    out << "    for (int i = 0; i < numberOfCases; i++) {\n";
    out << "        addCaseToSystem(cases[i]);\n";
    out << "    }\n\n";

    out << "    // Precedent Citations Graph\n";
    for (int i = 0; i < MAX_NODES; i++) {
        for (int j = 0; j < citationCount[i]; j++) {
            out << "    addCitationEdge(" << i << ", " << citationGraph[i][j] << ");\n";
        }
    }

    out << "\n    // Appeal Links\n";
    for (int i = 0; i < MAX_NODES; i++) {
        for (int j = 0; j < appealCount[i]; j++) {
            out << "    addAppealEdge(" << i << ", " << appealGraph[i][j] << ");\n";
        }
    }

    out << "\n    std::cout << \"[Comprehensive dataset loaded: \" << numberOfCases\n";
    out << "              << \" cases, \" << totalCitationCases() << \" citing cases, and \" << totalAppealCases() << \" appeal hierarchies]\\n\";\n";
    out << "}\n\n";
    out << "#endif // SAMPLE_DATA_H\n";

    out.close();
}

// ========== LOAD SAMPLE DATA ==========
#include "sample_data.h"

// ========== LOGIN FUNCTION ==========
bool login() {
    string username;
    string password;
    int attempts = 3;

    cout << "\n================= COURT PORTAL LOGIN =================\n";

    while (attempts > 0) {
        cout << "Enter Username: ";
        cin >> username;

        cout << "Enter Password: ";
        cin >> password;

        if (username == "admin" && password == "admin123") {
            cout << "\nLogin Successful! Welcome to the Judicial Portal.\n\n";
            return true;
        }

        attempts--;
        cout << "Invalid credentials! Attempts remaining: " << attempts << "\n\n";
    }

    cout << "Too many failed attempts. Access Denied.\n";
    return false;
}

// ---------- Menu Printing Functions ----------
void showMainMenu() {
    cout << "\n========== National Judicial Case Management System ==========\n";
    cout << "  1. CASE MANAGEMENT\n";
    cout << "  2. LEGAL ANALYTICS\n";
    cout << "  3. APPEAL TRACKING\n";
    cout << "  4. DASHBOARD\n";
    cout << "  5. Exit\n";
    cout << "===============================================================\n";
    cout << "  Choose option: ";
}

void caseManagementMenu() {
    int choice;

    do {
        cout << "\n--- Case Management ---\n";
        cout << "  1. Register New Case              (Queue)\n";
        cout << "  2. Process Filing Queue            (Queue - FIFO)\n";
        cout << "  3. Handle Urgent Case              (Priority Queue)\n";
        cout << "  4. Search Case by ID               (Binary Search)\n";
        cout << "  5. View All Cases                  (Sorted by Priority)\n";
        cout << "  6. Filter Cases by Type\n";
        cout << "  7. Update Case Status\n";
        cout << "  8. Schedule Hearing\n";
        cout << "  9. Go Back\n";
        cout << "  Choose option: ";
        cin >> choice;

        switch (choice) {
            case 1: registerCase(); break;
            case 2: processQueue(); break;
            case 3: handleUrgent(); break;
            case 4: searchCase(); break;
            case 5: viewAllCases(); break;
            case 6: filterByType(); break;
            case 7: updateStatus(); break;
            case 8: scheduleHearing(); break;
            case 9: break;
            default: cout << "\nInvalid choice.\n";
        }
    } while (choice != 9);
}

void legalAnalyticsMenu() {
    int choice;

    do {
        cout << "\n--- Legal Analytics ---\n";
        cout << "  1. Add Legal Citation               (Graph)\n";
        cout << "  2. Show Precedent Graph             (Graph)\n";
        cout << "  3. Most Influential Judgment         (Graph Analysis)\n";
        cout << "  4. Detect Circular Citations         (Cycle Detection)\n";
        cout << "  5. Go Back\n";
        cout << "  Choose option: ";
        cin >> choice;

        switch (choice) {
            case 1: addCitation(); break;
            case 2: showPrecedents(); break;
            case 3: mostInfluential(); break;
            case 4: detectCircularCitations(); break;
            case 5: break;
            default: cout << "\nInvalid choice.\n";
        }
    } while (choice != 5);
}

void appealTrackingMenu() {
    int choice;

    do {
        cout << "\n--- Appeal Tracking ---\n";
        cout << "  1. Add Appeal Link                   (Graph)\n";
        cout << "  2. Track Appeal Journey              (DFS)\n";
        cout << "  3. Go Back\n";
        cout << "  Choose option: ";
        cin >> choice;

        switch (choice) {
            case 1: addAppeal(); break;
            case 2: trackAppeal(); break;
            case 3: break;
            default: cout << "\nInvalid choice.\n";
        }
    } while (choice != 3);
}

void dashboardMenu() {
    int choice;

    do {
        cout << "\n--- Dashboard ---\n";
        cout << "  1. Show Dashboard Statistics\n";
        cout << "  2. Go Back\n";
        cout << "  Choose option: ";
        cin >> choice;

        switch (choice) {
            case 1: showDashboard(); break;
            case 2: break;
            default: cout << "\nInvalid choice.\n";
        }
    } while (choice != 2);
}

// ========== MAIN FUNCTION ==========
int main() {
    loadSampleData();

    if (!login()) {
        return 0;
    }

    int choice;

    do {
        showMainMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                caseManagementMenu();
                break;
            case 2:
                legalAnalyticsMenu();
                break;
            case 3:
                appealTrackingMenu();
                break;
            case 4:
                dashboardMenu();
                break;
            case 5:
                cout << "\nThank you! System closed.\n";
                break;
            default:
                cout << "\nInvalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
