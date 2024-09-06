import { RelayPool } from 'nostr'

const mises = "55472e9c01f37a35f6032b9b78dade386e6e4c57d80fd1d0646abb39280e5e27"
const damus = "wss://relay.damus.io/"
const scsi = "wss://nostr-pub.wellorder.net"
const relays = [damus]//, scsi]

const pool = RelayPool(relays)

pool.on('open', relay => {
    relay.subscribe("subid", {limit: 1, kinds:[3], authors: [mises]})
});

pool.on('eose', relay => {
    relay.close()
});

pool.on('event', (relay, sub_id, event) => {
    //console.log(event)   
    console.log("follows", event.tags.length);

    const content = JSON.parse(event.content);
    for(let rel in content){
        if(!relays.includes(rel))
            relays.push(rel);

        console.log(rel);
    }
});
