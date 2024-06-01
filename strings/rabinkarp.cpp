int Rabin_Karp(string source, string target) {
    // If either string is empty, return -1 as no valid match exists
    if (source == "" || target == "") return -1;
    
    int m = target.size();  // Length of the target string
    int power = 1;          // Variable to store the highest power of the base (31)
    
    // Calculate the highest power of 31 modulo BASE (used for removing the leading digit)
    for (int i = 0; i < m; i++) {
        power = (power * 31) % BASE;
    }
    
    int targetCode = 0;  // Hash code for the target string
    // Compute the hash code for the target string
    for (int i = 0; i < m; i++) {
        targetCode = (targetCode * 31 + target[i]) % BASE;
    }
    
    int hashCode = 0;  // Hash code for the current substring of the source string
    // Iterate through the source string
    for (int i = 0; i < source.size(); i++) {
        hashCode = (hashCode * 31 + source[i]) % BASE;  // Update hash code by adding the current character
        
        // Skip until the first complete substring of length m is formed
        if (i < m - 1) continue;
        
        // When beyond the first complete substring, remove the leading character's contribution
        if (i >= m) {
            hashCode = (hashCode - source[i - m] * power) % BASE;
        }
        
        // If hashCode becomes negative, adjust it by adding BASE
        if (hashCode < 0) {
            hashCode += BASE;
        }
        
        // Compare the hash codes and then the actual substring to avoid collisions
        if (hashCode == targetCode) {
            // If hash codes match, check the actual substring to confirm match
            if (source.substr(i - m + 1, m) == target) {
                return i - m + 1;  // Return the starting index of the match
            }
        }
    }
    
    // If no match is found, return -1
    return -1;
}
