# convertfasta
Convert multi line fasta format to single line format in lightening speed.


## compile from source
    git clone https://github.com/yazhinia/convertfasta.git
    cd convertfasta
    bash build.sh or g++ -o convertfasta_multi2single convertfasta_multi2single.cpp
    export PATH=$PATH:$(pwd)
    
## command line
`convertfasta_multi2single input.fasta`

### test run
`convertfasta_multi2single test.fasta`
