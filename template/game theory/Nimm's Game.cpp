// n 堆石子，a[0], a[1], ... , a[n-2], a[n-1]
// 两人轮流取石子，每次可取任一堆中的任意个石子，取走最后一堆石子的人获胜
// 必败态: a[0] ^ a[1] ^ ... ^ a[n-2] ^ a[n-1] == 0
// 任意非必败态都可转为必败态：

int NimSum = 0;
rep(i, 0, n) NimSum ^= a[i];
if (NimSum == 0) return !puts("No");
rep(i, 0, n) {
    int New = a[i] ^ NimSum;
    if (New < a[i]) {
        printf("%d %d\n", a[i], New);
        // 将 a[i] 转换为 New 即可达到必败态
    }
}

// 当每步的转移有个数限制时，则可使用 SG 函数
// 必败态：sg[a[0]] ^ sg[a[1]] ^ ... ^ sg[a[n-2]] ^ sg[a[n-1]] == 0

// 当规则改为：取走最后一堆石子的人失败
// if 所有堆中石子数量不全为1，则使用原策略，必胜态赢，必败态输
// else 所有堆中石子数量全为1，奇数堆为输，偶数堆为赢
