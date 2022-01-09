# Bookstore
# 基础指令
quit
exit

# 账户系统指令
su [User-ID] ([Password])?
logout
register [User-ID] [Password] [User-Name]
passwd [User-ID] ([Old-Password])? [New-Password]
useradd [User-ID] [Password] [Priority] [User-Name]
delete [User-ID]

security [Question] [Answer]
find [User_ID]

# 图书系统指令
show (-ISBN=[ISBN] | -name="[Book-Name]" | -author="[Author]" | -keyword="[Keyword]")?
buy [ISBN] [Quantity]
select [ISBN]
modify (-ISBN=[ISBN] | -name="[Book-Name]" | -author="[Author]" | -keyword="[Keyword]" | -price=[Price])+
import [Quantity] [Total-Cost]

# 日志系统指令
report myself
show finance ([Time])?
report finance
report employee
log
