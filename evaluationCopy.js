var programOutputXpath = `//div[@class="ui-widget vpl_ide_accordion_c_comments ui-accordion-content ui-corner-bottom ui-helper-reset ui-widget-content ui-accordion-content-active"]/div[2]/pre[2]/i`

copy($x(programOutputXpath)[0].innerText);