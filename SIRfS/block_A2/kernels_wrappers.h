cudaError_t launch_conv2mat_kernel(int** i0, int** j0, int oi, int oj, int maskRows, int maskCols, int** idx);
cudaError_t launch_getBorderNormals_computePatch(Matrix2D<bool> &mask, Matrix2D<double> &P, int **d_vector, std::vector<Matrix2D<bool> >  &patch_vector, int **counter, int P_rows, int mask_rows, int mask_cols);
cudaError_t launch_borderNormals_compute_temp_a(int **ii, int **jj, int dim, Matrix2D<bool>& temp_a);
cudaError_t launch_borderNormals_compute_maskedP(Matrix2D<double>& P, bool *allNonZeroLines, int *notzero_lines_in_P, int mask_rows, int mask_cols);


