
class Solution:
    def partitionLabels(self, S):
        """
        :type S: str
        :rtype: List[int]
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
