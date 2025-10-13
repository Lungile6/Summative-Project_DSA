#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main() {
    Graph graph;
    initializeGraph(&graph);

    // Seed with some example devices and connections
    addDevice(&graph, "D001");
    addDevice(&graph, "D002");
    addDevice(&graph, "D003");
    addDevice(&graph, "D004");
    addDevice(&graph, "D005");
    addDevice(&graph, "D006");
    addDevice(&graph, "D007");
    addDevice(&graph, "D008");

    addConnection(&graph, "D001", "D002");
    addConnection(&graph, "D001", "D003");
    addConnection(&graph, "D002", "D004");
    addConnection(&graph, "D003", "D005");
    addConnection(&graph, "D004", "D005");
    addConnection(&graph, "D004", "D006");
    addConnection(&graph, "D005", "D007");
    addConnection(&graph, "D006", "D008");

    int running = 1;
    while (running) {
        printf("\nDevice Mapping Menu:\n");
        printf("1. Add device\n");
        printf("2. Add connection (directed)\n");
        printf("3. Add connection (bidirectional)\n");
        printf("4. Remove connection\n");
        printf("5. Remove device\n");
        printf("6. Show outgoing connections\n");
        printf("7. Show incoming connections\n");
        printf("8. Show both incoming and outgoing\n");
        printf("9. Show adjacency matrix\n");
        printf("0. Exit\n");
        printf("Select an option: ");

        int choice = -1;
        if (scanf("%d", &choice) != 1) {
            // Invalid input, clear and continue
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            continue;
        }

        char a[32], b[32];
        switch (choice) {
            case 1:
                printf("Enter new device ID: ");
                scanf("%31s", a);
                if (addDevice(&graph, a) == 0) {
                    printf("Device %s added.\n", a);
                } else {
                    printf("Failed to add device (limit reached or error).\n");
                }
                break;
            case 2:
                printf("Enter from-device ID: ");
                scanf("%31s", a);
                printf("Enter to-device ID: ");
                scanf("%31s", b);
                addConnection(&graph, a, b);
                break;
            case 3:
                printf("Enter device A ID: ");
                scanf("%31s", a);
                printf("Enter device B ID: ");
                scanf("%31s", b);
                addBidirectionalConnection(&graph, a, b);
                break;
            case 4:
                printf("Enter from-device ID: ");
                scanf("%31s", a);
                printf("Enter to-device ID: ");
                scanf("%31s", b);
                removeConnection(&graph, a, b);
                break;
            case 5:
                printf("Enter device ID to remove: ");
                scanf("%31s", a);
                if (removeDevice(&graph, a) == 0) {
                    printf("Device %s removed.\n", a);
                } else {
                    printf("Device not found.\n");
                }
                break;
            case 6:
                printf("Enter device ID: ");
                scanf("%31s", a);
                displayConnections(&graph, a);
                break;
            case 7:
                printf("Enter device ID: ");
                scanf("%31s", a);
                displayIncomingConnections(&graph, a);
                break;
            case 8:
                printf("Enter device ID: ");
                scanf("%31s", a);
                displayBothConnections(&graph, a);
                break;
            case 9:
                displayAdjacencyMatrix(&graph);
                break;
            case 0:
                running = 0;
                break;
            default:
                printf("Invalid option.\n");
                break;
        }
    }

    freeGraph(&graph);
    return 0;
}
