# Assignment 2 — Q11: Social Network Graph Representation

**Course:** PCCST303 – Data Structures and Algorithms
**Graph used (given in the question):**
Vertices: A, B, C, D, E, F
Edges: A–B, A–C, B–D, B–E, C–F, E–F

---

## (a) Implementation: Adjacency Matrix and Adjacency List

### Adjacency Matrix (as built and printed by `adjacency_matrix.c`)

|   | A | B | C | D | E | F |
|---|---|---|---|---|---|---|
| A | 0 | 1 | 1 | 0 | 0 | 0 |
| B | 1 | 0 | 0 | 1 | 1 | 0 |
| C | 1 | 0 | 0 | 0 | 0 | 1 |
| D | 0 | 1 | 0 | 0 | 0 | 0 |
| E | 0 | 1 | 0 | 0 | 0 | 1 |
| F | 0 | 0 | 1 | 0 | 1 | 0 |

Storage: a fixed 6×6 array of ints = **36 cells** (12 of them non-zero, since each of the 6 edges is stored twice, symmetrically).

### Adjacency List (as built and printed by `adjacency_list.c`)

```
A -> B C
B -> A D E
C -> A F
D -> B
E -> B F
F -> C E
```

Storage: one linked-list node per (vertex, neighbour) pair = **2 × E = 12 nodes** total, each holding a vertex id and a pointer.

---

## BFS and DFS from vertex A

Both programs produced the **same visiting order** (the neighbour order in the list was built to match the row order in the matrix), but they reach that order by doing very different amounts of work internally.

**BFS order:** A → B → C → D → E → F
**DFS order:** A → B → D → E → F → C

### Trace Table — BFS(A)

| Step | Vertex dequeued | Neighbours examined | Newly enqueued | Queue after step | Visited set |
|---|---|---|---|---|---|
| 1 | – (init) | – | A | [A] | {A} |
| 2 | A | B, C | B, C | [B, C] | {A,B,C} |
| 3 | B | A(✗), D, E | D, E | [C, D, E] | {A,B,C,D,E} |
| 4 | C | A(✗), F | F | [D, E, F] | {A,B,C,D,E,F} |
| 5 | D | B(✗) | – | [E, F] | {A,B,C,D,E,F} |
| 6 | E | B(✗), F(✗) | – | [F] | {A,B,C,D,E,F} |
| 7 | F | C(✗), E(✗) | – | [] | {A,B,C,D,E,F} |

*(✗ = already visited, skipped)*

**Measured neighbour-scan cost:**
- Adjacency Matrix version scans a full row of 6 cells for every dequeued vertex → 6 vertices × 6 = **36 cell inspections**.
- Adjacency List version only walks each vertex's real neighbour list → total inspections = sum of degrees = 2E = **12 pointer hops**.

### Trace Table — DFS(A) (recursive call stack)

| Call | Vertex visited | Neighbour list checked | Recursive call made | Returns to |
|---|---|---|---|---|
| dfs(A) | A | B, C | dfs(B) | – |
| dfs(B) | B | A(✗), D, E | dfs(D) | dfs(A) |
| dfs(D) | D | B(✗) | – (backtrack) | dfs(B) |
| dfs(B) resumes | – | E | dfs(E) | – |
| dfs(E) | E | B(✗), F | dfs(F) | dfs(B) |
| dfs(F) | F | C, E(✗) | dfs(C) | dfs(E) |
| dfs(C) | C | A(✗), F(✗) | – (backtrack) | dfs(F)→dfs(E)→dfs(B)→dfs(A) |

---

## (b) Search Operation — Locate/Verify a Specified Edge

"Locating a vertex's connection" was implemented as an **edge-existence search**: given two vertex labels, determine whether they are directly connected, and count the elementary operations used.

### Trace Table — Edge Search

| Query (u,v) | Expected | Matrix: operations | Matrix: how | List: operations | List: how |
|---|---|---|---|---|---|
| A–C | Exists | 1 | Direct index `adjMatrix[A][C]` | 2 | Walk A's list: B(miss)→C(hit) |
| B–E | Exists | 1 | Direct index `adjMatrix[B][E]` | 3 | Walk B's list: A(miss)→D(miss)→E(hit) |
| A–F | Not present | 1 | Direct index `adjMatrix[A][F]` | 2 | Walk A's list: B(miss)→C(miss)→end |
| D–F | Not present | 1 | Direct index `adjMatrix[D][F]` | 1 | Walk D's list: B(miss)→end |

**Observation:** the matrix always costs exactly **1 operation** regardless of the graph, because it is a direct array lookup. The list costs **1 operation per neighbour inspected**, i.e. up to `degree(u)` operations — cheap for low-degree vertices (like D, degree 1) but more expensive for higher-degree vertices (like B, degree 3).

---

## (c) Comparative Analysis

| Criterion | Adjacency Matrix | Adjacency List |
|---|---|---|
| **Space used (this graph, V=6, E=6)** | 36 cells (fixed, `V²`) | 12 nodes (`2E`) |
| **Space complexity (general)** | O(V²) | O(V + E) |
| **BFS/DFS traversal cost (measured)** | 36 cell inspections | 12 pointer hops |
| **BFS/DFS time complexity (general)** | O(V²) | O(V + E) |
| **Edge-existence search (measured)** | Always 1 op | 1–3 ops (up to `deg(u)`) |
| **Edge-existence time complexity (general)** | O(1) | O(V) worst case, O(deg(u)) typical |
| **Add a new edge** | O(1) | O(1) (insert at head) |
| **Ease of finding "all neighbours of X"** | Must scan whole row (O(V)) | Already isolated as a list (O(deg(X))) |

---

## Time & Space Complexity Summary

| Algorithm / Structure | Time Complexity | Space Complexity |
|---|---|---|
| Adjacency Matrix (build) | O(V²) | O(V²) |
| Adjacency List (build) | O(V + E) | O(V + E) |
| BFS on Matrix | O(V²) | O(V) (queue + visited array) |
| BFS on List | O(V + E) | O(V) (queue + visited array) |
| DFS on Matrix | O(V²) | O(V) (recursion stack) |
| DFS on List | O(V + E) | O(V) (recursion stack) |
| Edge search on Matrix | O(1) | O(1) |
| Edge search on List | O(V) worst case | O(1) |

---

## Final Conclusion

For this 6-vertex, 6-edge network the graph is **sparse**: only 6 of the 15 possible pairs of vertices (`V(V−1)/2`) are actually connected. The execution results confirm the standard trade-off:

- The **adjacency matrix** always answers "are u and v connected?" in exactly **1 operation**, no matter how large or sparse the graph — its weakness is that it pays a fixed **O(V²)** cost in both space and traversal time even when most of those V² cells are wasted zeros (24 of the 36 matrix cells here are 0).
- The **adjacency list** stores only what actually exists (**O(V+E)** space — 12 nodes instead of 36 cells) and both BFS and DFS only ever touch real edges (**12 pointer hops** instead of **36 cell inspections**), at the cost of a slightly more expensive edge-existence check (1–3 comparisons here, and up to O(V) in the worst case for a high-degree vertex).

**Social networks in practice are large and sparse** — a person is typically connected to a small fraction of the total user base, so E grows roughly linearly with V rather than quadratically. Under that condition, O(V²) space and traversal cost become prohibitive as the network scales, while O(V+E) stays manageable.

**Therefore, the Adjacency List is the more suitable representation for a sparse social network.** It should only be reconsidered in favour of the Adjacency Matrix if the application's dominant operation is very frequent, repeated "are these two specific people connected?" queries on a dense sub-graph, where the matrix's O(1) lookup outweighs its memory cost.
