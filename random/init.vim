:set number
:set autoindent
:set tabstop=4
:set smarttab
:set softtabstop=4
:set mouse=a


call plug#begin()

Plug 'https://github.com/preservim/nerdtree' " NerdTree
Plug 'https://github.com/vim-airline/vim-airline' " Status bar
Plug 'EdenEast/nightfox.nvim' " Colorscheme

" autocomplete
" pip install jedi (should already have)
" pip install pynvim (shoule already have)
" install deoplete and deoplete-complete plugins below
" set path to python exe
Plug 'deoplete-plugins/deoplete-jedi' " https://github.com/deoplete-plugins/deoplete-jedi
Plug 'Shougo/deoplete.nvim' " https://github.com/Shougo/deoplete.nvim

set encoding=UTF-8

call plug#end()

let g:python3_host_prog='insert_path_to_python.exe'
let g:python_host_prog='insert_path_to_python.exe'
let g:deoplete#enable_at_startup = 1

:colorscheme carbonfox
