let gauss = (x, y) =>
  (1 / (2 * Math.PI)) * Math.pow(Math.E, -((x * x + y * y) / 2));

let matrix = Array(5)
  .fill()
  .map((_) => Array(5));

let norm = gauss(2, 2);

for (let i = -2; i < 3; ++i) {
  for (let j = -2; j < 3; ++j) {
    matrix[i + 2][j + 2] = Math.floor(gauss(i, j) / norm);
  }
}

console.table(matrix);

let sum = 0;
matrix.forEach((a) => a.forEach((e) => (sum += e)));
console.log(sum);
