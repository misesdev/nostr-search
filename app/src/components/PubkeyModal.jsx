import { useState } from "react";
import Modal from "react-bootstrap/Modal";
import Button from 'react-bootstrap/Button'

export default function PubkeyModal(isOpen = false, onClose) {

    const [pubkey, setPubkey] = useState('');

    const saveChages = () => {
        localStorage.setItem("pubkey", pubkey)
        onClose(false)
    }

    return (
        <div> 
            <Modal 
                show={isOpen}
                onHide={onClose}
                backdrop="static"
                keyboard={false}
            >
                <Modal.Header closeButton>
                    <Modal.Title>Add Your Pubkey</Modal.Title>
                </Modal.Header>

                <Modal.Body>
                    <p>Modal body text goes here.</p>
                    <input 
                        value={pubkey} 
                        onKeyUp={(e) => setPubkey(e.value)} 
                    />
                </Modal.Body>

                <Modal.Footer>
                    {/* <button onClick={() => onClose(false)} className="bg-red-700 text-white px-6 py-2 font-medium rounded-md hover:brightness-105 hover:shadow-md transition-shadow">Close</button> */}
                    {/* <button onClick={saveChages} className="bg-[#3e2eb3] text-white px-6 py-2 font-medium rounded-md hover:brightness-105 hover:shadow-md transition-shadow">Save changes</button> */}
                </Modal.Footer>
            </Modal>
        </div>
    )
}


