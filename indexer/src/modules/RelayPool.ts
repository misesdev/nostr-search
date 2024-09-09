import { WebSocket } from "ws"
import { Event, Filter } from "./types"
import { getPubkeys } from "../utils";

export class RelayPool {

    private relays: string[];
    public resultEvents: Event[] = [];
    public websockets: WebSocket[] = [];
    public pubkeys: string[] = [];
    private subscription: string = "3da979448d9ba263864c4d6f14984c42";
    //private pubkey: string;

    constructor(relays: string[], author: string) {
        if(relays.length < 1)
            throw Error("expected relays");

        this.relays = relays; 
        //this.pubkey = author;
        this.pubkeys = [author];
    }

    private async connectRelay(relay: string) : Promise<WebSocket> {
        return new Promise((resolve, reject) => {
            let websock = new WebSocket(relay);
            websock.on("open", () => resolve(websock));
            websock.on("message", (message) => {
                let data = JSON.parse(message.toString());            
                if(data[0] == "EVENT") {
                    let event: Event = data[2];
                    let npubs = getPubkeys(event)
                        .filter((pub: string) => !this.pubkeys.includes(pub))
                    npubs.forEach(pub => this.pubkeys.push(pub))
                    console.log("found users", event.tags.length)
                    if(this.resultEvents.filter(e => e.id == event.id).length <= 0) {
                        this.resultEvents.push(event)
                    }
                }
            })
            websock.on("close", () => reject(`not connetd: ${relay}`))
            websock.on("error", () => reject(`not connetd: ${relay}`))
        });
    }

    public async connect() {
        for(let i = 0; i < this.relays.length; i++) {
            let socket = await this.connectRelay(this.relays[i])
                .catch(error => console.log(error))
            if(socket) {
                this.websockets.push(socket);
            }
        } 
    }

    private async fetchEventRelay(socket: WebSocket, filter: Filter) {
        return new Promise((resolve) => {
            socket.send(`[
                "REQ", 
                "${this.subscription}", 
                ${JSON.stringify(filter)}
            ]`);
            setTimeout(() => resolve(true), 500)
        });
    }

    public async fechEvent(filter: Filter): Promise<Event[]> { 
        for(let i = 0; i < this.websockets.length; i++) {
            await this.fetchEventRelay(this.websockets[i], filter)
        } 
        return this.resultEvents;
    }

    public async fetchUser(pubkey: string): Promise<Event> {
        let events = await this.fechEvent({
            kinds: [0],
            authors: [pubkey],
            limit: 1
        });

        if(events.length <= 0) return null;

        return events[0];
    }
}
