#include <stdio.h>

int main() {
    // Open a file for writing
    FILE *dataFile = fopen("output.dat", "w");

    if (!dataFile) {
        printf("Error opening data file!\n");
        return 1;
    }

    // Triangle vertices with new coordinates
    fprintf(dataFile, "%d %d\n",  1, -1);     // A
    fprintf(dataFile, "%d %d\n", -4,  6);     // B
    fprintf(dataFile, "%d %d\n", -3, -5);     // C
    fprintf(dataFile, "%d %d\n",  1, -1);     // A
    fprintf(dataFile, "%d %d\n", -4,  6);     // B
    fprintf(dataFile, "%d %d\n", -3, -5);     // C
    fprintf(dataFile, "%d %d\n",  1, -1);     // A
    fprintf(dataFile, "%d %d\n", -4,  6);     // B
    fprintf(dataFile, "%d %d\n",  2,  0);     // E
    fprintf(dataFile, "%lf %lf\n", 1.54054054 , -1.75675676);     // F
    fprintf(dataFile, "%lf %lf\n", -3.32786885, -1.39344262);     // D
    fprintf(dataFile, "%d %d\n",  2,  0);     // E
    
    
    // Close the file
    fclose(dataFile);

    FILE *dashedAHFile = fopen("dashedAH.dat", "w");
    if (!dashedAHFile) {
        printf("Error opening dashedAH data file!\n");
        return 1;
    }
    fprintf(dashedAHFile, "%lf %lf\n", 2.83333333 , -0.83333333);     // H
    fprintf(dashedAHFile, "%d %d\n",  1, -1);     // A
    fclose(dashedAHFile);

    FILE *dashedEHFile = fopen("dashedEH.dat", "w");
    if (!dashedEHFile) {
        printf("Error opening dashedEH data file!\n");
        return 1;
    }
    fprintf(dashedEHFile, "%d %d\n", 2 , 0);     // E
    fprintf(dashedEHFile, "%lf %lf\n", 2.83333333 , -0.83333333);     // H
    fclose(dashedEHFile);

    FILE *dashedFHFile = fopen("dashedFH.dat", "w");
    if (!dashedFHFile) {
        printf("Error opening dashedFH data file!\n");
        return 1;
    }
    fprintf(dashedFHFile, "%lf %lf\n", 1.54054054, -1.75675676);     // F
    fprintf(dashedFHFile, "%lf %lf\n", 2.83333333 , -0.83333333);     // H
    fclose(dashedFHFile);

    FILE *dashedAEFile = fopen("dashedAE.dat", "w");
    if (!dashedAEFile) {
        printf("Error opening dashedAE data file!\n");
        return 1;
    }
    fprintf(dashedAEFile, "%d %d\n",  1, -1);     // A
    fprintf(dashedAEFile, "%d %d\n", 2 , 0);     // E
    fclose(dashedAEFile);

    FILE *dashedAFFile = fopen("dashedAF.dat", "w");
    if (!dashedAFFile) {
        printf("Error opening dashedAF data file!\n");
        return 1;
    }
    fprintf(dashedAFFile, "%d %d\n",  1, -1);     // A
    fprintf(dashedAFFile, "%lf %lf\n", 1.54054054, -1.75675676);     // F
    fclose(dashedAFFile);




    // Use Gnuplot to plot the data file
    FILE *gnuplotPipe = popen("gnuplot -persist", "w");

    if (gnuplotPipe) {
        // Send commands to Gnuplot
        fprintf(gnuplotPipe, "set xrange [-9:8]\n"); // Set x-axis range
        fprintf(gnuplotPipe, "set yrange [-6:7]\n"); // Set y-axis range
        fprintf(gnuplotPipe, "set grid\n");          // Enable grid lines


        // Labels for starting points
        fprintf(gnuplotPipe, "set label 'A' at 1.1,-1\n");
        fprintf(gnuplotPipe, "set label 'B' at -3.9,6\n");
        fprintf(gnuplotPipe, "set label 'C' at -2.9,-5\n");
        fprintf(gnuplotPipe, "set label 'D' at -3.22786885, -1.39344262\n");
        fprintf(gnuplotPipe, "set label 'E' at 2/1 , 0\n");
        fprintf(gnuplotPipe, "set label 'F' at 1.74054054, -1.75675676\n");
        fprintf(gnuplotPipe, "set label 'H' at 2.93333333 , -0.83333333\n");
        

        // Plot commands with separate titles for AB, BC, and CA
        fprintf(gnuplotPipe, "plot 'output.dat' using 1:2 every 4::0 with linespoints pointtype 7 title  'AB', '' every 4::1 with linespoints pointtype 7 title 'BC', '' every 4::2 with linespoints pointtype 7 title 'CA', 'dashedAH.dat' using 1:2 with lines lt 1 dt 2 title 'Dashed AH', 'dashedEH.dat' using 1:2 with lines lt 1 dt 2 title 'Dashed EH', 'dashedFH.dat' using 1:2 with lines lt 1 dt 2 title 'Dashed FH', 'dashedAE.dat' using 1:2 with lines lt 1 dt 2 title 'Dashed AE', 'dashedAF.dat' using 1:2 with lines lt 1 dt 2 title 'Dashed AF'\n");
        fflush(gnuplotPipe);



        printf("Press enter to exit...");
        getchar();

        // Close the Gnuplot pipe
        fprintf(gnuplotPipe, "exit\n");
        pclose(gnuplotPipe);
    } else {
        printf("Gnuplot not found. Please install Gnuplot to use this program.\n");
    }

    return 0;
}
