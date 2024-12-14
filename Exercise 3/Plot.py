import pandas as pd
import matplotlib.pyplot as plt

bst_df = pd.read_csv('bst_exact_results.csv')
approx_df = pd.read_csv('2approx_results.csv')

#process time and identify "No solution found" or "Skipped"
def process_time_and_errors(df):
    no_solution_bst_indices = []
    skipped_bst_indices = []
    
    for i, row in df.iterrows():
        # Check if the Computation Time (seconds) is a string and contains "No solution found" or "Skipped"
        if isinstance(row['Computation Time (seconds)'], str):
            if "No solution found" in row['Computation Time (seconds)']:
                no_solution_bst_indices.append(i)
            elif "Skipped" in row['Computation Time (seconds)']:
                skipped_bst_indices.append(i)

    # Convert to numeric values for valid entries, replace invalid entries with NaN
    df['Computation Time (seconds)'] = pd.to_numeric(df['Computation Time (seconds)'], errors='coerce')
    return no_solution_bst_indices, skipped_bst_indices, df


no_solution_bst_indices, skipped_bst_indices, bst_df = process_time_and_errors(bst_df)
_, _, approx_df = process_time_and_errors(approx_df)  #Same processing for approx_df if needed


plt.figure(figsize=(12, 6))


index_bst = range(1, len(bst_df) + 1)
index_approx = range(1, len(approx_df) + 1)

#BST Exact results
plt.scatter(index_bst, bst_df['Computation Time (seconds)'], 
            color='blue', label='BST Exact', marker='o', alpha=0.7)

#"No solution found" (purple X markers)
plt.scatter([index_bst[i] for i in no_solution_bst_indices], 
            [-0.5] * len(no_solution_bst_indices),  # Set y-value to -0.5 for error points
            color='purple', label='No solution found', marker='X', s=100)

#"Skipped" (red circle markers)
plt.scatter([index_bst[i] for i in skipped_bst_indices], 
            [-0.5] * len(skipped_bst_indices),  # Set y-value to -0.5 for error points
            color='red', label='Segmentation fault / Skipped', marker='o', s=100)

#2-Approx results
plt.scatter(index_approx, approx_df['Computation Time (seconds)'], 
            color='green', label='2-Approx', marker='o', alpha=0.7)


plt.title('Running Time Comparison of Vertex Cover Algorithms')
plt.xlabel('Input Index (1-200)')
plt.ylabel('Computation Time (seconds)')
plt.xticks(range(1, 201))  # Set x-ticks to show indices from 1 to 200
plt.ylim(-1, max(bst_df['Computation Time (seconds)'].max(), approx_df['Computation Time (seconds)'].max()) + 1)  # Adjust y-limits to accommodate error points
plt.legend()
plt.grid()


plt.tight_layout()
plt.savefig('running_time_comparison.png')
plt.show()
