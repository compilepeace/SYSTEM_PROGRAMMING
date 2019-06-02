
.PHONY: clean

T1= 1_dns_resolver
T2= 2_simple_client
T3= 3_simple_webserver
T4= 4_network_interfaces
T5= 5_UDP_server
TARGETS= $(T1) $(T2) $(T3) $(T4) $(T5)
 

all: $(TARGETS)


$(T1): $(T1).c
	gcc $< -o $@

$(T2): $(T2).c
	gcc $< -o $@

$(T3): $(T3).c
	gcc $< -o $@

$(T4): $(T4).c
	gcc $< -o $@

$(T5):$(T5).c
	gcc $< -o $@


clean:
	rm $(T1) $(T2) $(T3) $(T4) $(T5)
