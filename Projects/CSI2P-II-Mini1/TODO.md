# Optimization
Build the Data-Operation DAG by finding the identifiers in the assmebly code or directly from the AST.
```C
struct Data {
  Operation *prev, *next;
  int val, id, regs;
  bool used, leaf;
}
```

```C
struct Operation {
  Data *in[2], *out[2];
  Type T;
  int regs;
}
```
# Memory Optimization
Simply load x, y, z to register when the program begins. Store the register back to memory when the program ends.

# Constant Value Optimization
We enumerate all the possibile inputs and oberserve the value of the registers. If a certain node's value stays constant no matter the input is, we mark that register as constant.

# Branch Compression
On the DAG, if two pathes $p1$ and $p2$ have the equivalent operations, then `p1` and `p2` can be compressed into one branch.

# Symbolic Substitution Optimization
```
A * 3 (TAKES 30 CYCLE)
A + A + A (TAKES 20 CYCLE)
```
Multiplication and Addition are substitute to each other. Therefore, by substitute the operation to alternative form, we may reduce the total cycle.

- `A + 0` would be assign.
- `A + A + A` would be `A * 3`
- `LOAD [0] r0 & STORE r0 [0]` would be nothing.

# Branch Cut Optimization
From the register which storage our final output, we dfs backward to the very beginning of the Data-Operation flow.
During the process of dfs, mark every single node used, which is the only nodes are necessary to exist.
Other branches & nodes are unnecessary and can be removed without concern.
The `CPY` operation with only one output can be removed as if removing a node from linked list.

# Register Optimization
`regs` represents how much registers is needed for calculate the value of this node. We calculate `regs` of each nodes by dynamic programming.
- If the `Data` node has `prev`, then the `regs` would be `prev`.`regs`. Otherwise, it is `0`.
- If the `Operation` is `CPY`, the `regs` would be the `regs` of predecessor increment by `1`.
- Otherwise, if `Operation.in[0].regs` < `Operation.in[1].regs` and the operation is swappable, we swap `in[0]` and `in[1]`. The value of `Operation.regs` would be `max(in[0].regs, 1 + in[1].regs)`.
