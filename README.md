# 2.1 Project Title
# National Judicial Case Management System

# 2.2 Problem Statement
Case Study 189: National Judicial Case Management System
## Introduction
Judicial systems handle millions of legal cases annually. Managing case registrations, prioritizing
urgent matters, scheduling hearings, and retrieving records efficiently are critical for delivering
timely justice. The National Judicial Case Management System is designed to streamline court
operations through intelligent case management and legal analytics.
## Objective
The objective is to manage nationwide case records, prioritize urgent matters, automate
scheduling, and provide instant access to legal information.
##Industry Context
Courts process diverse case types, including criminal, civil, constitutional, and commercial
disputes. Efficient case management improves transparency and reduces delays.
## Case Registration Using Queue
Newly filed cases enter a Queue and are processed in filing order, ensuring fairness and
transparency.
## Urgent Matter Handling Using Priority Queue
Emergency cases, bail applications, and constitutional matters are prioritized using a Priority
Queue.
## Case Retrieval Using Binary Search
Case records are stored in sorted databases, enabling rapid retrieval through Binary Search.
## Legal Precedent Analysis Using Graphs
Judicial citations form a graph structure where cases are nodes and citations are edges. Graph
analysis identifies influential judgments and precedent relationships.
## Appeal Tracking Using DFS
DFS traces appeal histories from lower courts to higher courts, providing complete legal case
journeys.
## Deliverables
The system provides digital court dashboards, automated hearing scheduling, legal analytics,
precedent discovery, appeal tracking, and case search portals.
## Conclusion
The National Judicial Case Management System demonstrates how Queue, Priority Queue,
Binary Search, Graphs, and DFS can modernize judicial administration and improve access to
justice.

---
# 2.3 Objectives
- To manage nationwide case records securely and efficiently.
- To prioritize urgent matters (e.g., bail applications, constitutional emergencies).
- To automate queue processing for fair filing procedures.
- To provide instant access to legal precedents and case histories.
- To trace appeal journeys across judicial hierarchies.
- **Educational Objective:** To accomplish all the above using a pure, manual Data Structures and Algorithms (DSA) implementation in C++ without relying on standard library templates (STL).

# 2.4 System Overview / Architecture
The system operates as a unified terminal application segmented into four core portals:
1. **Case Management:** Handles filing, urgent case processing, case searching, and status updates.
2. **Legal Analytics:** Manages citation networks to find influential judgments and detects logical loops (circular citations).
3. **Appeal Tracking:** Traces cases from lower courts up to the Supreme Court.
4. **Dashboard:** Provides live statistical summaries of the court's load.

The program reads and auto-saves to a header file (`sample_data.h`) for data persistence.

# 2.5 Data Structures and Algorithms Used
- **Arrays (1D & 2D):** Used as the foundational memory structure for cases and graphs.
- **Queue (FIFO):** Manages the standard case filing queue ensuring chronological fairness.
- **Priority Queue (Max-Heap):** Manages urgent cases ensuring higher priority cases are heard first.
- **Graphs (Adjacency List):** Maps citation networks and appeal hierarchies using 2D arrays.
- **Depth-First Search (DFS):** Recursively traverses the graphs to trace appeal journeys.
- **Cycle Detection Algorithm:** Uses a 3-state DFS tracker (`unvisited`, `visiting`, `processed`) to detect circular citations.
- **Binary Search:** Retrieves case records in $O(\log N)$ time.
- **Bubble Sort:** Sorts the central database to prepare it for Binary Search and user viewing.

# 2.6 Implementation Approach
The project strips away all C++ STL dependencies (`vector`, `queue`, `priority_queue`, `map`, `sort()`) to rigorously demonstrate DSA fundamentals:
- **Manual Indices:** The Queue is managed with custom `qFront` and `qRear` pointers.
- **Array-based Heap:** The Max-Heap is built using mathematical parent/child index calculations (`(i-1)/2`, `2i+1`, `2i+2`) with manual bubble-up and heapify-down logic.
- **Custom Search/Sort:** Implementation of custom `swapCases()` and iterative loops for sorting and binary searching.
- **Auto-Persistence Engine:** A unique I/O function that dynamically rewrites the `sample_data.h` C++ file at runtime so data is preserved across compilations.

# 2.7 Time and Space Complexity Analysis
- **Register Case (Queue Enqueue):** Time: $O(1)$ | Space: $O(N)$
- **Process Filing (Queue Dequeue):** Time: $O(1)$ | Space: $O(N)$
- **Handle Urgent Case (Heap Insert/Extract):** Time: $O(\log N)$ | Space: $O(N)$
- **Search Case (Binary Search):** Time: $O(N^2)$ to sort + $O(\log N)$ to search | Space: $O(1)$
- **Most Influential Judgment (Graph traversal):** Time: $O(V+E)$ | Space: $O(V)$
- **Detect Circular Citations / Appeal Tracking (DFS):** Time: $O(V+E)$ | Space: $O(V)$ for recursive stack depth.
*(Where $N$ is the number of cases, $V$ is the number of nodes, and $E$ is the number of edges).*

# 2.8 Execution Steps
1. Ensure you have a C++ compiler (like `g++`) installed on your system.
2. Open a terminal and navigate to the project directory:
   ```bash
   cd "/Users/pratikswain/Desktop/new dsa case study/"
   ```
3. Compile the source code:
   ```bash
   g++ nationalcourt.cpp -o nationalcourt
   ```
4. Run the executable:
   ```bash
   ./nationalcourt
   ```
5. Follow the on-screen menus to navigate the system.

# 2.9 Sample Inputs and Outputs

The following is a sequential walkthrough of interacting with the system:

### Step 1: Navigating the Main Menu
**Input:**
```text
========== National Judicial Case Management System ==========
  1. CASE MANAGEMENT
  2. LEGAL ANALYTICS
  3. APPEAL TRACKING
  4. DASHBOARD
  5. Exit
===============================================================
  Choose option: 1
```

### Step 2: Registering a New Case (Queue)
**Input:**
```text
--- Case Management ---
  1. Register New Case              (Queue)
  2. Process Filing Queue            (Queue - FIFO)
  ...
  Choose option: 1

Enter Case ID: 501
Enter Title: Corporate Fraud: State vs MegaCorp
Enter Type (Criminal/Civil/Constitutional/Commercial): Commercial
Enter Priority (1-10): 8
```
**Output:**
```text
Case 501 registered successfully!
```

### Step 3: Handling Urgent Matters (Priority Queue)
**Input:**
```text
  Choose option: 3
```
**Output:**
```text
--- Highest Priority Case ---
ID: 105 | Title: Murder Trial: State vs. Rao | Priority: 10 | Status: Registered
```

### Step 4: Searching for a Case (Binary Search)
**Input:**
```text
  Choose option: 4

Enter Case ID to search: 501
```
**Output:**
```text
--- Case Found ---
ID       : 501
Title    : Corporate Fraud: State vs MegaCorp
Type     : Commercial
Priority : 8
Status   : Registered
Hearing  : Not Scheduled
```

### Step 5: Detecting Circular Citations (Graph / Cycle Detection)
**Input (from Legal Analytics Menu):**
```text
--- Legal Analytics ---
  1. Add Legal Citation               (Graph)
  2. Show Precedent Graph             (Graph)
  3. Most Influential Judgment         (Graph Analysis)
  4. Detect Circular Citations         (Cycle Detection)
  5. Go Back
  Choose option: 4
```
**Output:**
```text
[WARNING] Circular Citation Detected!
```

### Step 6: Tracking an Appeal (Depth-First Search)
**Input (from Appeal Tracking Menu):**
```text
--- Appeal Tracking ---
  1. Add Appeal Link                   (Graph)
  2. Track Appeal Journey              (DFS)
  3. Go Back
  Choose option: 2

Enter Starting Case ID: 101
```
**Output:**
```text
Appeal Journey: 101 -> 201 -> 301 -> 401 -> END
```

### Step 7: Viewing the Dashboard Statistics
**Input (from Dashboard Menu):**
```text
  Choose option: 1
```
**Output:**
```text
============= COURT DASHBOARD =============
 Total Cases        : 22
-------------------------------------------
 By Status:
   Registered       : 21
   Scheduled        : 1
   Under Hearing    : 0
   Resolved         : 0
-------------------------------------------
 Urgent Cases (P>=7): 8
 Pending in Queue   : 21
 Citations Recorded : 15
 Appeal Links       : 7
=============================================
```

# 2.10 Screenshots
<img width="725" height="848" alt="Screenshot 2026-06-15 at 8 49 59 PM" src="https://github.com/user-attachments/assets/a258d2e3-4105-402d-954f-4b4182643f32" />
<img width="742" height="846" alt="Screenshot 2026-06-15 at 8 50 57 PM" src="https://github.com/user-attachments/assets/cacacb40-c234-4395-a7fd-11752ea73878" />
<img width="578" height="841" alt="Screenshot 2026-06-15 at 8 52 34 PM" src="https://github.com/user-attachments/assets/5048bb3f-c795-4995-b517-e918d49d894d" />
<img width="717" height="769" alt="Screenshot 2026-06-15 at 8 54 36 PM" src="https://github.com/user-attachments/assets/a334e54d-417d-431d-b208-017cc0db09d0" />
<img width="823" height="811" alt="Screenshot 2026-06-15 at 8 56 36 PM" src="https://github.com/user-attachments/assets/ac6b00d4-f848-4792-8657-31b0340204b0" />
<img width="745" height="805" alt="Screenshot 2026-06-15 at 8 57 37 PM" src="https://github.com/user-attachments/assets/a75b9280-4652-4e00-9101-08251c52a769" />


# 2.11 Results and Observations
The system successfully mimics a high-volume judicial environment. 
- The **Priority Queue** successfully ensured that Constitutional and severe Criminal cases were extracted before standard Civil disputes, bypassing the FIFO queue entirely.
- The **Graph logic** reliably identified the most cited precedent (Case 103) and correctly halted infinite loops when cyclical citations (120 -> 121 -> 122 -> 120) were tested.
- The implementation proved that complex organizational problems can be solved strictly with fundamental DSA without standard library overhead.

# 2.12 Conclusion
The National Judicial Case Management System successfully modernizes court administration by integrating classical algorithms with real-world logical requirements. It guarantees fairness via Queues, urgency via Heaps, and robust analytical mapping via Graphs and Depth-First Search. This project serves as a comprehensive demonstration of memory-efficient data management and manual algorithmic design.


** Github Repo Link:-  https://github.com/pratikswain070-blip/National-Judicial-Case-Management-System
