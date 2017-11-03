"=========================================================================
"" DesCRiption: 适合自己使用的vimrc文件，for Linux/Windows, GUI/Console
"
"" Last Change: 2010年08月02日 15时13分
"
"" Version:     1.80
"
""=========================================================================
set tags=/root/linux-3.17.2/tags
set nocompatible            " 关闭 vi 兼容模式
syntax on                   " 自动语法高亮
set number                  " 显示行号
set autoindent              " 自动对齐
set smartindent             " 智能对齐
"set cursorline              " 突出显示当前行
set ruler                   " 打开状态栏标尺
set ts=4                    " 设定 tab 长度为 4
"set tabstop=1               " 设定 tab 长度为 4
set expandtab               " use space instead of tab
set shiftwidth=0            " 设定 > 命令移动时的宽度为 4
set softtabstop=4           " 使得按退格键时可以一次删掉 4 个空格
set nobackup                " 覆盖文件时不备份
set autochdir               " 自动切换当前目录为当前文件所在的目录
filetype plugin indent on   " 开启插件
set backupcopy=yes          " 设置备份时的行为为覆盖
set ignorecase smartcase    " 搜索时忽略大小写，但在有一个或以上大写字母时仍保持对大小写敏感
set nowrapscan              " 禁止在搜索到文件两端时重新搜索
set incsearch               " 输入搜索内容时就显示搜索结果
set hlsearch                " 搜索时高亮显示被找到的文本
set noerrorbells            " 关闭错误信息响铃
set novisualbell            " 关闭使用可视响铃代替呼叫
set t_vb=                   " 置空错误铃声的终端代码
" set showmatch               " 插入括号时，短暂地跳转到匹配的对应括号
" " set matchtime=2             " 短暂跳转到匹配括号的时间
" set magic                   " 设置魔术
" set hidden                  " 允许在有未保存的修改时切换缓冲区，此时的修改由
" vim 负责保存
" set guioptions-=T           " 隐藏工具栏
" set guioptions-=m           " 隐藏菜单栏
" set smartindent             " 开启新行时使用智能自动缩进
set backspace=indent,eol,start
"                             " 不设定在插入状态无法用退格键和 Delete
"                             键删除回车符
"                             set cmdheight=1             " 设定命令行的行数为
"                             1
"                             set laststatus=2            " 显示状态栏
"                             (默认值为 1, 无法显示状态栏)
"                             set statusline=\ % @=((foldclosed(line('.'))
"                                                         " 用空格键来开关折叠
"                                                         " return OS type,
"                                                         eg: windows, or
"                                                         linux, mac, et.st..
"                                                         function! MySys()
"                                                             if has("win16")
"                                                             || has("win32")
"                                                             || has("win64")
"                                                             || has("win95")
"                                                                     return
"                                                                     "windows"
"                                                                         elseif
"                                                                         has("unix")
"                                                                                 return
"                                                                                 "linux"
"                                                                                     endif
if has("autocmd")
au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif
endif
set tags=tags;
set autochdir

nnoremap <silent> <F8> :TlistToggle<CR><CR> 
let Tlist_Show_One_File=0
let Tlist_Exit_OnlyWindow=1
let Tlist_Use_Left_Window=1
let Tlist_File_Fold_Auto_Close=1

"新建.c,.h,.sh,.java文件，自动插入文件头 
autocmd BufNewFile *.cpp,*.[ch],*.sh,*.java exec ":call SetTitle()" 
""定义函数SetTitle，自动插入文件头 
    func SetTitle() 
    "如果文件类型为.sh文件 
    if &filetype == 'sh' 
        call setline(1,"\#########################################################################") 
        call append(line("."), "\# File Name: ".expand("%")) 
        call append(line(".")+1, "\# Author: zhangxinxin") 
        call append(line(".")+2, "\# mail: 694041531@qq.com") 
        call append(line(".")+3, "\# Created Time:".strftime("%c")) 
        call append(line(".")+4,"\#########################################################################") 
        call append(line(".")+5,"\#!/bin/bash") 
        call append(line(".")+6,"") 
    else 
        call setline(2,          "/**********************************************************") 
        call append(line(".")+1, "*    > File Name: ".expand("%"))
        call append(line(".")+2, "*    > Author: zhangxinxin") 
        call append(line(".")+3, "*    > Mail: 694041531@qq.com ") 
        call append(line(".")+4, "*    > Created Time: ".strftime("%c")) 
        call append(line(".")+5, "**********************************************************/") 
        call append(line(".")+6, "")
     endif
    
     "if &filetype == 'cpp'
     "   call append(line(".")+7, "#include<iostream>")
     "   call append(line(".")+8, "using namespace std;")
     "   call append(line(".")+9, "")
     "endif
     
     "if &filetype == 'c'
     "   call append(line(".")+7, "#include<stdio.h>")
     "   call append(line(".")+8, "")
    "endif
    
    "新建文件后，自动定位到文件末尾
    autocmd BufNewFile * normal G

endfunc 

function! s:insert_gates()
let gatename = substitute(toupper(expand("%:t")), "\\.", "_", "g")
execute "normal! i#ifndef _" . gatename
execute "normal! o#define _" . gatename
execute "normal! Go#endif // _" . gatename
normal! kk
endfunction
autocmd BufNewFile *.{h,hpp,H} call <SID>insert_gates()

map <F5> :call CompileRunGcc()<CR>
func! CompileRunGcc()
    exec "w"
    if &filetype == 'c'
        exec "!g++ % -o %<"
        exec "! ./%<"
    elseif &filetype == 'cpp'
        exec "!g++ % -o %<"
        exec "! ./%<"
    elseif &filetype == 'java' 
        exec "!javac %" 
        exec "!java %<"
    elseif &filetype == 'sh'
        :!./%
    endif
endfunc

map <F6> :call Rungdb()<CR>
func! Rungdb()
    exec "w"
    exec "!g++ % -g -o %<"
    exec "!gdb ./%<"
endfunc
"set foldenable      "允许折叠
"set foldmethod=indent       "手动折叠
"设置字体 以及中文支持
if has("win32")
set guifont=Inconsolata:h12:cANSI
endif

" 配置多语言环境
if has("multi_byte")
" UTF-8 编码
set encoding=utf-8
set termencoding=utf-8
set formatoptions+=mM
set fencs=utf-8,gbk

if v:lang =~? '^\(zh\)\|\(ja\)\|\(ko\)'
set ambiwidth=double
endif

if has("win32")
source $VIMRUNTIME/delmenu.vim
source $VIMRUNTIME/menu.vim
language messages zh_CN.utf-8
endif
else
echoerr "Sorry, this version of (g)vim was not compiled with +multi_byte"
endif

"回车不添加注释
autocmd FileType * setlocal formatoptions-=c formatoptions-=r formatoptions-=o
