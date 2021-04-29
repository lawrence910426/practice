module Comparator_4bits (A, B, A_lt_B, A_gt_B, A_eq_B);
// declare input signals
input [4-1:0] A;
input [4-1:0] B;

// declare output signals
output A_lt_B, A_gt_B, A_eq_B;

// declare wires
wire [4-1:0] nA;
wire [4-1:0] nB;
wire [4-1:0] X;

wire [4-1:0] A_and_nB;
wire [4-1:0] nA_and_B;

wire [4-1:0] gt_component;
wire [4-1:0] lt_component;

// gate descriptions

not (nA[0], A[0]);
not (nA[1], A[1]);
not (nA[2], A[2]);
not (nA[3], A[3]);

not (nB[0], B[0]);
not (nB[1], B[1]);
not (nB[2], B[2]);
not (nB[3], B[3]);

and (A_and_nB[0], A[0], nB[0]);
and (A_and_nB[1], A[1], nB[1]);
and (A_and_nB[2], A[2], nB[2]);
and (A_and_nB[3], A[3], nB[3]);

and (nA_and_B[0], nA[0], B[0]);
and (nA_and_B[1], nA[1], B[1]);
and (nA_and_B[2], nA[2], B[2]);
and (nA_and_B[3], nA[3], B[3]);

nor (X[0], A_and_nB[0], nA_and_B[0]);
nor (X[1], A_and_nB[1], nA_and_B[1]);
nor (X[2], A_and_nB[2], nA_and_B[2]);
nor (X[3], A_and_nB[3], nA_and_B[3]);

and (A_eq_B, X[0], X[1], X[2], X[3]);

and (gt_component[0], X[1], X[2], X[3], A[0], nB[0]);
and (gt_component[1], X[2], X[3], A[1], nB[1]);
and (gt_component[2], X[3], A[2], nB[2]);
and (gt_component[3], A[3], nB[3]);

or (A_gt_B, gt_component[0], gt_component[1], gt_component[2], gt_component[3]);

and (lt_component[0], X[1], X[2], X[3], nA[0], B[0]);
and (lt_component[1], X[2], X[3], nA[1], B[1]);
and (lt_component[2], X[3], nA[2], B[2]);
and (lt_component[3], nA[3], B[3]);

or (A_lt_B, lt_component[0], lt_component[1], lt_component[2], lt_component[3]);

endmodule




