int net[N];     // net[i] 表示 p[0] 到 p[i-1] 的最长公共前后缀长度
char s[N], p[N];
struct KMP {
    void Get(char *p, int m) {
        net[0] = -1;
        for (int i = 0, j = -1; i < m;) {
            if (j == -1 || p[i] == p[j]) net[++i] = ++j;
            else j = net[j];
        }
        // 最小循环节长度
        // if (m % (m - net[m]) == 0) return m - net[m]; else return m;
        // 最小循环节个数
        // if (m % (m - net[m]) == 0) return m / (m - net[m]); else return 1;
    }
    int kmp(char *s, int n, char *p, int m) {
        Get(p, m);
        for (int i = 0, j = 0; i < n;) {
            if (j == -1 || s[i] == p[j]) ++i, ++j;
            else j = net[j];
            if (j == m) return i - j;   // 第一个匹配成功的 s 串下标
            //if (j == m) cnt++, j = 0;     // 母串中可匹配的不相交模式串个数
        }
        return -1;
    }
};

================================================== Problem Set ==================================================

// hdu 4763
// 判断一段字符串是否是 EAEBE 的形式， A 和 B 的长度可以不等，求最长的子串 E 的长度
// 先用整个字符串作为模式串，匹配后三分之一的字符串，得到前后缀相同的各个位置
// 再用整个字符串作为模式串，匹配当前前缀之后的字符串，判断是否能匹配，记录最大长度

struct KMP {
    void Get(char *p, int m) {
        net[0] = -1;
        for (int i = 0, j = -1; i < m;) {
            if (j == -1 || p[i] == p[j]) net[++i] = ++j;
            else j = net[j];
        }
    }
    // 先用整个字符串作为模式串，匹配后三分之一的字符串，得到前后缀相同的各个位置
    void kmp1(char *s, int n, char *p, int m) {
        for (int i = 0, j = 0; i < n;) {
            if (j == -1 || s[i] == p[j]) ++i, ++j;
            else j = net[j];
            if (i == n) {
                S.insert(j-1);      // 当匹配成功时，记录下最长能匹配到的前缀下标
                --i;
                j = net[j-1];       // 当作失配，重新匹配
            }
            if (i == n-1 && j == -1) return;    // 已经没有前缀可以匹配
        }
    }
    // 再用整个字符串作为模式串，匹配当前前缀之后的中间的字符串，判断是否能匹配
    bool kmp(char *s, int n, char *p, int m) {
        for (int i = 0, j = 0; i < n;) {
            if (j == -1 || s[i] == p[j]) ++i, ++j;
            else j = net[j];
            if (j == m) return true;
        }
        return false;
    }
};
KMP obj;

int Solve() {
    while (n--) {
        S.clear();
        scanf("%s", s);
        int len = strlen(s);
        if (len < 3) { puts("0"); continue; }
        obj.Get(s, len);
        obj.kmp1(s+len-len/3, len/3, s, len);   // 寻找各个相同前后缀的位置
        int ans = 0;
        for (auto i : S) {
            bool ok = obj.kmp(s+i+1, len-2*i-2, s, i+1);    // 匹配中间字符串
            if (ok) ans = i + 1;    // 记录最大长度
        }
        printf("%d\n", ans);
    }
}

----------------------------------------------------------------------------------------------------

// 查找字符串中所有循环子串的个数
// 循环字符串即可以分成若干个相同的子串，如 abcabc 可以分成两个 abc

struct KMP {
    int Get(char *p, int m) {
        net[0] = -1;
        for (int i = 0, j = -1; i < m;) {
            if (j == -1 || p[i] == p[j]) {
                net[++i] = ++j;
                // 注意这部分代码必须放在当前 if 内，否则放在外面会因为 j 的跳转造成重复计算
                // 也可以在主程序中调用完 Get() 后，再去寻找循环串
                if (i % (i - net[i]) == 0 && i / (i - net[i]) != 1) {   // i - net[i] 为最小循环节长度
                    cnt++;      // 对于每一个子串右端点，判断是否为循环串
                }
            }
            else j = net[j];
        }
    }
};

int Solve() {
    int len = strlen(str);
    cnt = 0;
    rep(i, 0, len) obj.Get(str+i, len - i);  // 枚举子串起点
    return !printf("%d\n", cnt);
}
