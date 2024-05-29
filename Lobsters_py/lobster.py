class Lobster:
    def __init__(self, name, size, value):
        self.name = name
        self.size = size
        self.value = value

def dynamic_programming_lobster(lobster_collection, lobster_number, bag_size, output):
    dp = [[0 for _ in range(bag_size + 1)] for _ in range(lobster_number + 1)]
    
    for i in range(1, lobster_number + 1):
        for w in range(1, bag_size + 1):
            if lobster_collection[i-1].size <= w:
                dp[i][w] = max(lobster_collection[i-1].value + dp[i-1][w-lobster_collection[i-1].size], dp[i-1][w])
            else:
                dp[i][w] = dp[i-1][w]
    
    max_value = dp[lobster_number][bag_size]

    j = lobster_number
    k = bag_size
    while j > 1 and k > 1:  
        if dp[j][k] != dp[j-1][k]:
            output.write(f"{lobster_collection[j-1].name}\n")  
            k -= lobster_collection[j-1].size  
        j -= 1


    output.write(f"Maximum value: {max_value}\n")
	
