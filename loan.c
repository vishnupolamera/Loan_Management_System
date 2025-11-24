#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LOANS 100

struct Loan {
    int loanID;
    char borrowerName[50];
    float principal;
    float rate; // annual interest rate percent
    int tenure; // in months
    int status; // 1 for active, 0 for repaid
};

struct Loan loans[MAX_LOANS];
int loanCount = 0;

float calcEMI(float principal, float rate, int tenure) {
    float monthlyRate = rate / (12 * 100);
    float emi = principal * monthlyRate * pow(1 + monthlyRate, tenure) / (pow(1 + monthlyRate, tenure) - 1);
    return emi;
}

void addLoan() {
    if(loanCount >= MAX_LOANS) {
        printf("Max loan limit reached.");
        return;
    }
    struct Loan l;
    l.loanID = loanCount + 1;
    printf("Enter borrower name: ");
    scanf("%s", l.borrowerName);
    printf("Enter principal amount: ");
    scanf("%f", &l.principal);
    printf("Enter annual interest rate percentage: ");
    scanf("%f", &l.rate);
    printf("Enter tenure (months): ");
    scanf("%d", &l.tenure);
    l.status = 1;
    loans[loanCount++] = l;
    printf("Loan added. Assigned Loan ID: %d", l.loanID);
}

void showLoans() {
    printf("--- Loan Details ---");
    for(int i = 0; i < loanCount; i++) {
        printf("ID: %d | Name: %s | Principal: %.2f | Rate: %.2f | Tenure: %d months | EMI: %.2f | Status: %s",
            loans[i].loanID, loans[i].borrowerName, loans[i].principal, loans[i].rate, loans[i].tenure,
            calcEMI(loans[i].principal, loans[i].rate, loans[i].tenure),
            loans[i].status ? "Active" : "Repaid");
    }
}

void markAsRepaid() {
    int id;
    printf("Enter Loan ID to mark as repaid: ");
    scanf("%d", &id);
    for(int i = 0; i < loanCount; i++) {
        if(loans[i].loanID == id) {
            loans[i].status = 0;
            printf("Loan ID %d marked as repaid.", id);
            return;
        }
    }
    printf("Loan ID not found!");
}

int main() {
    int choice;
    while(1) {
        printf("--- Loan Management System ---\n");
        printf("1. Add new loan\n");
        printf("2. Show all loans\n");
        printf("3. Mark loan as repaid\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: addLoan(); break;
            case 2: showLoans(); break;
            case 3: markAsRepaid(); break;
            case 4: exit(0);
            default: printf("Invalid choice!");
        }
    }
    return 0;
}