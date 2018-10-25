

all::

run:
	@$(MAKE) -C .. $@

%:
	@$(MAKE) -C ext $@

rdoc:
	rdoc --main Main.rb --op html

clean:
	@$(RM) *~
	@$(MAKE) -C ext $@
