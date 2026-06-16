#ifndef SAMPLE_DATA_H
#define SAMPLE_DATA_H

#include <iostream>
#include <string>

struct Case;
void addCaseToSystem(Case c);
void addCitationEdge(int from, int to);
void addAppealEdge(int lower, int higher);
int totalCitationCases();
int totalAppealCases();

// This file gives the program ready-made data for testing.
void loadSampleData() {
    Case cases[] = {
        {101, "State vs. Sharma (Theft Case)", "Criminal", 4, "Registered", "Not Scheduled"},
        {105, "Murder Trial: State vs. Rao", "Criminal", 10, "Registered", "Not Scheduled"},
        {110, "Homicide Case: State vs. Vikram", "Criminal", 10, "Registered", "Not Scheduled"},
        {115, "Assault & Battery: State vs. Verma", "Criminal", 5, "Registered", "Not Scheduled"},
        {102, "Land Boundary Dispute: Patel vs. Gupta", "Civil", 3, "Registered", "Not Scheduled"},
        {106, "Property Rights: Desai vs. Mehta", "Civil", 2, "Registered", "Not Scheduled"},
        {111, "Divorce & Custody: Sen vs. Sen", "Civil", 3, "Registered", "Not Scheduled"},
        {112, "Defamation Suit: Kapoor vs. Puri", "Civil", 4, "Registered", "Not Scheduled"},
        {103, "Bail Application: State vs. Khan", "Constitutional", 9, "Registered", "Not Scheduled"},
        {107, "Fundamental Rights Petition (Freedom of Speech)", "Constitutional", 8, "Registered", "Not Scheduled"},
        {113, "Writ Petition: Environmental Pollution Action", "Constitutional", 9, "Registered", "Not Scheduled"},
        {104, "Trade Fraud: ABC vs. XYZ Corp", "Commercial", 5, "Registered", "Not Scheduled"},
        {108, "Contract Breach: TechCo vs. DataInc", "Commercial", 6, "Registered", "Not Scheduled"},
        {109, "Corporate Tax Evasion: Alpha Ltd", "Commercial", 7, "Registered", "Not Scheduled"},
        {114, "Intellectual Property: TechSoft vs. AppCorp", "Commercial", 8, "Registered", "Not Scheduled"},
        {116, "Bankruptcy Filing: RetailGlobal Group", "Commercial", 6, "Registered", "Not Scheduled"},
        {120, "Patent Dispute: Inventions Inc vs. Creators Ltd", "Commercial", 6, "Registered", "Not Scheduled"},
        {121, "Copyright Infringement: MediaHouse vs. NetBroadcasting", "Commercial", 5, "Registered", "Not Scheduled"},
        {122, "Trademark Opposition: BrandA vs. BrandB", "Commercial", 6, "Registered", "Not Scheduled"},
        {12, "robbery of house", "civil", 6, "Registered", "Not Scheduled"}
    };

    int numberOfCases = sizeof(cases) / sizeof(cases[0]);

    // Add every sample case to the main array, queue, and urgent heap.
    for (int i = 0; i < numberOfCases; i++) {
        addCaseToSystem(cases[i]);
    }

    // Precedent Citations Graph
    addCitationEdge(104, 103);
    addCitationEdge(104, 101);
    addCitationEdge(104, 102);
    addCitationEdge(105, 103);
    addCitationEdge(105, 101);
    addCitationEdge(107, 103);
    addCitationEdge(108, 104);
    addCitationEdge(108, 102);
    addCitationEdge(109, 104);
    addCitationEdge(113, 103);
    addCitationEdge(114, 103);
    addCitationEdge(114, 104);
    addCitationEdge(114, 102);
    addCitationEdge(115, 101);
    addCitationEdge(116, 104);
    addCitationEdge(116, 108);
    addCitationEdge(120, 121);
    addCitationEdge(121, 122);
    addCitationEdge(122, 120);

    // Appeal Links
    addAppealEdge(101, 201);
    addAppealEdge(102, 202);
    addAppealEdge(105, 205);
    addAppealEdge(201, 301);
    addAppealEdge(202, 302);
    addAppealEdge(205, 305);
    addAppealEdge(301, 401);

    std::cout << "[Comprehensive dataset loaded: " << numberOfCases
              << " cases, " << totalCitationCases() << " citing cases, and " << totalAppealCases() << " appeal hierarchies]\n";
}

#endif // SAMPLE_DATA_H
