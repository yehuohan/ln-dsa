
class Solution:
    def partitionLabels(self, S):
        """
        :type S: str
        :rtype: List[int]
        """

        """
        # 容易理解，但速度太慢
        num = []
        while S:
            k = 1
            # 两个集合没有交集，即可分开
            while not set(S[:k]).isdisjoint(set(S[k:])):
                k += 1
            num.append(k)
            S = S[k:]
        return num
        """

        p = []
        for k in range(len(S)):
            # p中无含有S[k]的字符串
            flg = False
            index = -1
            for i in range(len(p)):
                if S[k] in p[i]:
                    # p中有含有S[k]的字符串
                    index = i
                    flg = True
                    break
            p.append(S[k])
            if flg:
                # 合并index到len(p)的字符串
                for i in range(index+1, len(p)):
                    p[index] += p[i]
                p = p[0:index+1]
        num = []
        for k in p:
            num.append(len(k))
        return num


if __name__ == "__main__":
    su = Solution()
    print(su.partitionLabels("ababcbacadefegdehijhklij"))
