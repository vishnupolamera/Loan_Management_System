#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LOANS 100

struct Loan {
    int loanID;
    char borrowerName[50];
    float principal;
    float rate;   // annual interest rate percent
    int tenure;   // in months
    int status;   // 1 for active, 0 for repaid
};

struct Loan loans[MAX_LOANS];
int loanCount = 0;

float calcEMI(float principal, float rate, int tenure) {
    float monthlyRate = rate / (12 * 100);
    float emi = principal * monthlyRate * pow(1 + monthlyRate, tenure) /
                (pow(1 + monthlyRate, tenure) - 1);
    return emi;
}

void addLoan() {
    if (loanCount >= MAX_LOANS) {
        printf("Max loan limit reached.\n");
        return;
    }
    struct Loan l;
    l.loanID = loanCount + 1;
    printf("Enter borrower name: ");
    scanf(" %[^\n]", l.borrowerName); // allows spaces
    printf("Enter principal amount: ");
    scanf("%f", &l.principal);
    printf("Enter annual interest rate percentage: ");
    scanf("%f", &l.rate);
    printf("Enter tenure (months): ");
    scanf("%d", &l.tenure);
    l.status = 1;
    loans[loanCount++] = l;
    printf("Loan added. Assigned Loan ID: %d\n", l.loanID);
}

void showLoans() {
    printf("\n--- Loan Details ---\n");
    for (int i = 0; i < loanCount; i++) {
        printf("ID: %d | Name: %s | Principal: %.2f | Rate: %.2f | Tenure: %d months | EMI: %.2f | Status: %s\n",
               loans[i].loanID, loans[i].borrowerName, loans[i].principal,
               loans[i].rate, loans[i].tenure,
               calcEMI(loans[i].principal, loans[i].rate, loans[i].tenure),
               loans[i].status ? "Active" : "Repaid");
    }
}

void markAsRepaid() {
    int id;
    printf("Enter Loan ID to mark as repaid: ");
    scanf("%d", &id);
    for (int i = 0; i < loanCount; i++) {
        if (loans[i].loanID == id) {
            loans[i].status = 0;
            printf("Loan ID %d marked as repaid.\n", id);
            return;
        }
    }
    printf("Loan ID not found!\n");
}

void updateLoan() {
    int id;
    printf("Enter Loan ID to update: ");
    scanf("%d", &id);
    for (int i = 0; i < loanCount; i++) {
        if (loans[i].loanID == id) {
            printf("Updating Loan ID %d\n", id);
            printf("Enter new borrower name: ");
            scanf(" %[^\n]", loans[i].borrowerName);
            printf("Enter new principal amount: ");
            scanf("%f", &loans[i].principal);
            printf("Enter new annual interest rate: ");
            scanf("%f", &loans[i].rate);
            printf("Enter new tenure (months): ");
            scanf("%d", &loans[i].tenure);
            printf("Loan updated successfully!\n");
            return;
        }
    }
    printf("Loan ID not found!\n");
}

void deleteLoan() {
    int id;
    printf("Enter Loan ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < loanCount; i++) {
        if (loans[i].loanID == id) {
            for (int j = i; j < loanCount - 1; j++) {
                loans[j] = loans[j + 1]; // shift left
            }
            loanCount--;
            printf("Loan ID %d deleted successfully!\n", id);
            return;
        }
    }
    printf("Loan ID not found!\n");
}

int main() {
    int choice;
    while (1) {
        printf("\n--- Loan Management System ---\n");
        printf("1. Add new loan\n");
        printf("2. Show all loans\n");
        printf("3. Mark loan as repaid\n");
        printf("4. Update loan\n");
        printf("5. Delete loan\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addLoan(); break;
            case 2: showLoans(); break;
            case 3: markAsRepaid(); break;
            case 4: updateLoan(); break;
            case 5: deleteLoan(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}