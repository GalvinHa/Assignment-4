//TO DO: add your documentation here

// TO DO: implement the recursive series function
//      Hint: it should return a long long (integer)
long long seriesRecursive(int n) {
    // base case
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    if (n == 2) {
        return 1;
    }
    // recursive case
    return seriesRecursive(n - 1) + 2 * seriesRecursive(n - 2) + 4 * seriesRecursive(n - 3);
}


int main(int argc, char* argv[]) {
    // Read n from command line argument
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <n>" << std::endl;
        return 1;
    }
    int n = std::atoi(argv[1]);

    // Compute series value of n
    long long result = seriesRecursive(n);
    std::cout << "seriesRecursive(" << n << ") = " << result << std::endl;
    return 0;
}
