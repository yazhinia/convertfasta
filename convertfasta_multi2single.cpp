#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <chrono>
#include <filesystem>

bool condition_header(std::string &line) {
    if (line[0] == '>') {
        return true;
    }
    else {
        return false;
    }
}

void get_complete_sequence(std::ifstream &fasta, std::string &line, std::string &sequence) {
    fasta >> line;
    while (!condition_header(line) && !fasta.eof()) {
        sequence.append(line);
        fasta >> line;
    }
}


int main(int argc, char *argv[]) {

    if(argc != 2 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
    {
        std::cout << "provide input fasta file\n";
        return EXIT_SUCCESS;
    }
    
    else {
        auto start = std::chrono::high_resolution_clock::now();
        std::string contigs_sequences = argv[1]; 
        // std::string dir = std::filesystem::current_path(); 
        std::ifstream fasta(contigs_sequences);
        std::ofstream outfile("single_" + contigs_sequences);
        if (!fasta.is_open()) {
            std::cerr << "Error: Unable to open Fasta file!" << "\n";
            return 1;
        }

        std::string line, sequence;
        fasta >> line;

        unsigned int sequence_counter = 0;
        while (condition_header(line)) {
            outfile << line << "\n";
            sequence = "";
            get_complete_sequence(fasta, line, sequence);

            if (!sequence.empty()) {
                outfile << sequence << "\n";
            }
            else {
                std::cerr << "empty sequence for a header" << "\n";
                return 1;
            }
            sequence_counter++;
        }
        outfile.close();

        std::cout << sequence_counter << " sequences processed \n";
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
        std::cout << duration.count() << " seconds\n";
        return  EXIT_SUCCESS;
    }
}