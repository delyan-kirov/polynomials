local on_attach = require("plugins.configs.lspconfig").on_attach
local capabilities = require("plugins.configs.lspconfig").capabilities
local utils = require("lspconfig/util")
local lspconfig = require "lspconfig"

-- Define a table to map LSP servers to their associated file types
local server_filetypes = {
  html = { "html", "htmldjango" },
  cssls = { "css", "scss", "less" },
  tsserver = { "typescript", "javascript" },
  clangd = { "c", "cpp" },
  pyright = { "python" },
}

for lsp, filetypes in pairs(server_filetypes) do
  lspconfig[lsp].setup {
    on_attach = on_attach,
    capabilities = capabilities,
    filetypes = filetypes,  -- Specify the filetypes for each server
  }
end

-- 
-- lspconfig.pyright.setup { blabla}
