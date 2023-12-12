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
    getline(fasta, line);
    while (!condition_header(line) && !fasta.eof()) {
        sequence.append(line);
        getline(fasta, line);
    }
}


int main(int argc, char *argv[]) {

    if(argc != 3 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
    {
        std::cout << "Usage: convertfasta_multi2single input.fasta output_directory";
        return EXIT_SUCCESS;
    }
    
    else {
        auto start = std::chrono::high_resolution_clock::now();
        std::string contigs_sequences = argv[1];
        auto pos = contigs_sequences.find_last_of ('/');
        std::string outname;
        if (pos != std::string::npos) {
            outname = contigs_sequences.substr(pos+1);
        } else {
            outname = contigs_sequences;
        }
        std::string dir = argv[2];
        std::ifstream fasta(contigs_sequences);
        std::cout<<"Input file: " << contigs_sequences << "\n";
        std::cout<<"Output directory: " << dir << "\n";
        std::ofstream outfile(dir + "/single_" + outname);

        if (!fasta.is_open()) {
            std::cerr << "Error: Unable to open Fasta file!" << "\n";
            return 1;
        }

        std::string line, sequence;

        getline(fasta, line);

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